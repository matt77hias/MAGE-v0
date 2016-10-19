<?xml version="1.0"?><doc>
<members>
<member name="M:mage.AllocAligned(System.UInt64)" decl="false" source="c:\users\matthias\documents\visual studio 2015\projects\mage\mage\mage\src\memory\allocation.hpp" line="14">
<summary>
Allocates memory on an alignment boundary of 64 bytes.
</summary>
<param name="size">
The requested size in bytes to allocate in memory.
</param>
<returns>
A pointer to the memory block that was allocated or NULL if the operation failed.
The pointer is a multiple of the alignment of 64 bytes.
</returns>
</member>
<member name="M:mage.FreeAligned(System.Void*)" decl="false" source="c:\users\matthias\documents\visual studio 2015\projects\mage\mage\mage\src\memory\allocation.hpp" line="46">
<summary>
Frees a block of memory that was allocated with AllocAligned.
</summary>
<param name="ptr">
A pointer to the memory block that was allocated.
This function returns if <paramref name="ptr"/> points to NULL.
</param>
</member>
</members>
</doc>