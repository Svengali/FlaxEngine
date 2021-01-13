// Copyright (c) 2012-2021 Wojciech Figat. All rights reserved.

#include "NavMeshBoundsVolume.h"
#include "Engine/Level/Scene/Scene.h"
#if USE_EDITOR
#include "Editor/Editor.h"
#include "Editor/Managed/ManagedEditor.h"
#include "NavMeshBuilder.h"
#endif

NavMeshBoundsVolume::NavMeshBoundsVolume(const SpawnParams& params)
    : BoxVolume(params)
{
}

void NavMeshBoundsVolume::OnEnable()
{
    // Base
    Actor::OnEnable();

    GetScene()->NavigationVolumes.Add(this);
}

void NavMeshBoundsVolume::OnDisable()
{
    GetScene()->NavigationVolumes.Remove(this);

    // Base
    Actor::OnDisable();
}

#if USE_EDITOR

void NavMeshBoundsVolume::OnBoundsChanged(const BoundingBox& prevBounds)
{
    // Auto-rebuild modified navmesh area
    if (IsDuringPlay() && IsActiveInHierarchy() && !Editor::IsPlayMode && Editor::Managed->CanAutoBuildNavMesh())
    {
        BoundingBox dirtyBounds;
        BoundingBox::Merge(prevBounds, _box, dirtyBounds);
        NavMeshBuilder::Build(GetScene(), dirtyBounds, ManagedEditor::ManagedEditorOptions.AutoRebuildNavMeshTimeoutMs);
    }
}

Color NavMeshBoundsVolume::GetWiresColor()
{
    return Color::Green;
}

#endif
