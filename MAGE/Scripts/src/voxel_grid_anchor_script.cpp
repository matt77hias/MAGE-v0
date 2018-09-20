//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "voxel_grid_anchor_script.hpp"
#include "scene\camera\camera.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::script {

	VoxelGridAnchorScript::VoxelGridAnchorScript()
		: BehaviorScript() {}

	VoxelGridAnchorScript::VoxelGridAnchorScript(
		const VoxelGridAnchorScript& script) noexcept = default;

	VoxelGridAnchorScript::VoxelGridAnchorScript(
		VoxelGridAnchorScript&& script) noexcept = default;

	VoxelGridAnchorScript::~VoxelGridAnchorScript() = default;

	VoxelGridAnchorScript& VoxelGridAnchorScript::operator=(
		const VoxelGridAnchorScript& script) noexcept = default;

	VoxelGridAnchorScript& VoxelGridAnchorScript::operator=(
		VoxelGridAnchorScript&& script) noexcept = default;

	void VoxelGridAnchorScript::Load([[maybe_unused]] Engine& engine) {
		ThrowIfFailed(HasOwner(),
					  "This script needs to be attached to a node.");
	}

	void VoxelGridAnchorScript::Update([[maybe_unused]] Engine& engine) {
		const auto& transform = GetOwner()->GetTransform();
		auto position = Point3(XMStore< F32x3 >(transform.GetWorldOrigin()));
		rendering::VoxelizationSettings::SetVoxelGridCenter(std::move(position));
	}
}