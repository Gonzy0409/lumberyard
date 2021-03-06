/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/

#pragma once

#include "EditorBaseShapeComponent.h"
#include <AzFramework/Entity/EntityDebugDisplayBus.h>
#include <LmbrCentral/Shape/SplineComponentBus.h>
#include "TubeShapeComponent.h"

namespace LmbrCentral
{
    /**
     * Editor representation of a tube shape
     */
    class EditorTubeShapeComponent
        : public EditorBaseShapeComponent
        , private AzFramework::EntityDebugDisplayEventBus::Handler
        , private SplineComponentNotificationBus::Handler
        , private SplineAttributeNotificationBus::Handler
    {
    public:
        AZ_EDITOR_COMPONENT(EditorTubeShapeComponent, EditorTubeShapeComponentTypeId, EditorBaseShapeComponent);
        static void Reflect(AZ::ReflectContext* context);

        EditorTubeShapeComponent() = default;

        // AZ::Component
        void Activate() override;
        void Deactivate() override;

        // EditorComponentBase
        void BuildGameEntity(AZ::Entity* gameEntity) override;

    protected:
        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
        {
            EditorBaseShapeComponent::GetProvidedServices(provided);
            provided.push_back(AZ_CRC("TubeShapeService", 0x3fe791b4));
        }

        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required)
        {
            EditorBaseShapeComponent::GetRequiredServices(required);
            required.push_back(AZ_CRC("SplineService", 0x2b674d3c));
        }

    private:
        AZ_DISABLE_COPY_MOVE(EditorTubeShapeComponent)

        // AzFramework::EntityDebugDisplayEventBus
        void DisplayEntity(bool& handled) override;

        // SplineComponentNotificationBus
        void OnSplineChanged() override;

        // SplineAttributeNotificationBus
        void OnAttributeAdded(size_t index) override;
        void OnAttributeRemoved(size_t index) override;
        void OnAttributesSet(size_t size) override;
        void OnAttributesCleared() override;

        void ConfigurationChanged();
        void GenerateVertices();

        TubeShape m_tubeShape; ///< Underlying tube shape.
        TubeShapeMeshConfig m_tubeShapeMeshConfig; ///< Configuration to control how the TubeShape should look.
        ShapeMesh m_tubeShapeMesh; ///< Buffer to hold index and vertex data for TubeShape when drawing.
    };
} // namespace LmbrCentral
