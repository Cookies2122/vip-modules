#include "memaddr.h"

CMemory CMemory::FollowNearCall(const ptrdiff_t opcodeOffset, const ptrdiff_t nextInstructionOffset)
{
	return ResolveRelativeAddress(opcodeOffset, nextInstructionOffset);
}

CMemory CMemory::FollowNearCallSelf(const ptrdiff_t opcodeOffset, const ptrdiff_t nextInstructionOffset)
{
	return ResolveRelativeAddressSelf(opcodeOffset, nextInstructionOffset);
}

CMemory CMemory::ResolveRelativeAddress(const ptrdiff_t registerOffset, const ptrdiff_t nextInstructionOffset)
{
	const uintptr_t skipRegister = ptr + registerOffset;

	const int32_t relativeAddress = *reinterpret_cast<int32_t*>(skipRegister);

	const uintptr_t nextInstruction = ptr + nextInstructionOffset;

	return CMemory(nextInstruction + relativeAddress);
}

CMemory CMemory::ResolveRelativeAddressSelf(const ptrdiff_t registerOffset, const ptrdiff_t nextInstructionOffset)
{
	const uintptr_t skipRegister = ptr + registerOffset;

	const int32_t relativeAddress = *reinterpret_cast<int32_t*>(skipRegister);

	const uintptr_t nextInstruction = ptr + nextInstructionOffset;

	ptr = nextInstruction + relativeAddress;
	return *this;
}
