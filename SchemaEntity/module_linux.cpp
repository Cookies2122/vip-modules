
#include "module.h"
#include "memaddr.h"
#include <cstring>
#include <link.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

using namespace DynLibUtils;

CModule::~CModule()
{
	if (m_pModuleHandle)
		dlclose(m_pModuleHandle);
}

bool CModule::InitFromName(const std::string_view svModuleName, bool bExtension)
{
	if (m_pModuleHandle)
		return false;

	if (svModuleName.empty())
		return false;

	std::string sModuleName(svModuleName);
	if (!bExtension)
		sModuleName.append(".so");

	struct dl_data
	{
		ElfW(Addr) addr;
		const char* moduleName;
		const char* modulePath;
	} dldata{ 0, sModuleName.c_str(), {} };

	dl_iterate_phdr([](dl_phdr_info* info, size_t  , void* data)
	{
		dl_data* dldata = reinterpret_cast<dl_data*>(data);

		if (std::strstr(info->dlpi_name, dldata->moduleName) != nullptr)
		{
			dldata->addr = info->dlpi_addr;
			dldata->modulePath = info->dlpi_name;
		}

		return 0;
	}, &dldata);

	if (!dldata.addr)
		return false;

	if (!Init(dldata.modulePath))
		return false;

	return true;
}

bool CModule::InitFromMemory(const CMemory pModuleMemory)
{
	if (m_pModuleHandle)
		return false;

	if (!pModuleMemory)
		return false;

	Dl_info info;
	if (!dladdr(pModuleMemory, &info) || !info.dli_fbase || !info.dli_fname)
		return false;

	if (!Init(info.dli_fname))
		return false;

	return true;
}

bool CModule::Init(const std::string_view svModelePath)
{
	void* handle = dlopen(svModelePath.data(), RTLD_LAZY | RTLD_NOLOAD);
	if (!handle)
		return false;

	link_map* lmap;
	if (dlinfo(handle, RTLD_DI_LINKMAP, &lmap) != 0)
	{
		dlclose(handle);
		return false;
	}

	int fd = open(lmap->l_name, O_RDONLY);
	if (fd == -1)
	{
		dlclose(handle);
		return false;
	}

	struct stat st;
	if (fstat(fd, &st) == 0)
	{
		void* map = mmap(nullptr, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
		if (map != MAP_FAILED)
		{
			ElfW(Ehdr)* ehdr = static_cast<ElfW(Ehdr)*>(map);
			ElfW(Shdr)* shdrs = reinterpret_cast<ElfW(Shdr)*>(reinterpret_cast<uintptr_t>(ehdr) + ehdr->e_shoff);
			const char* strTab = reinterpret_cast<const char*>(reinterpret_cast<uintptr_t>(ehdr) + shdrs[ehdr->e_shstrndx].sh_offset);

			for (auto i = 0; i < ehdr->e_shnum; ++i)
			{
				ElfW(Shdr)* shdr = reinterpret_cast<ElfW(Shdr)*>(reinterpret_cast<uintptr_t>(shdrs) + i * ehdr->e_shentsize);
				if (*(strTab + shdr->sh_name) == '\0')
					continue;

				m_vModuleSections.emplace_back(strTab + shdr->sh_name, static_cast<uintptr_t>(lmap->l_addr + shdr->sh_addr), shdr->sh_size);
			}

			munmap(map, st.st_size);
		}
	}

	close(fd);

	m_pModuleHandle = handle;
	m_sModulePath.assign(svModelePath);

	m_ExecutableCode = GetSectionByName(".text");

	return true;
}

CMemory CModule::GetVirtualTableByName(const std::string_view svTableName, bool bDecorated) const
{
	if (svTableName.empty())
		return CMemory();

	CModule::ModuleSections_t readOnlyData = GetSectionByName(".rodata"), readOnlyRelocations = GetSectionByName(".data.rel.ro");
	if (!readOnlyData.IsSectionValid() || !readOnlyRelocations.IsSectionValid())
		return CMemory();

	std::string sDecoratedTableName(bDecorated ? svTableName : std::to_string(svTableName.length()) + std::string(svTableName));
	std::string sMask(sDecoratedTableName.length() + 1, 'x');

	CMemory typeInfoName = FindPattern(sDecoratedTableName.data(), sMask, nullptr, &readOnlyData);
	if (!typeInfoName)
		return CMemory();

	CMemory referenceTypeName = FindPattern(&typeInfoName, "xxxxxxxx", nullptr, &readOnlyRelocations);
	if (!referenceTypeName)
		return CMemory();

	CMemory typeInfo = referenceTypeName.Offset(-0x8);

	for (const auto& sectionName : { std::string_view(".data.rel.ro"), std::string_view(".data.rel.ro.local") })
	{
		CModule::ModuleSections_t section = GetSectionByName(sectionName);
		if (!section.IsSectionValid())
			continue;

		CMemory reference;
		while ((reference = FindPattern(&typeInfo, "xxxxxxxx", reference, &section)))
		{
			if (reference.Offset(-0x8).GetValue<int64_t>() == 0)
			{
				return reference.Offset(0x8);
			}

			reference.OffsetSelf(0x8);
		}
	}

	return CMemory();
}

CMemory CModule::GetFunctionByName(const std::string_view svFunctionName) const noexcept
{
	if (!m_pModuleHandle)
		return CMemory();

	if (svFunctionName.empty())
		return CMemory();

	return dlsym(m_pModuleHandle, svFunctionName.data());
}

CMemory CModule::GetModuleBase() const noexcept
{
	return static_cast<link_map*>(m_pModuleHandle)->l_addr;
}
