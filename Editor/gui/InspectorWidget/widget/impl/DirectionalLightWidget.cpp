#include "DirectionalLightWidget.h"

namespace editor::impl {

	DirectionalLightWidget::DirectionalLightWidget(QWidget* parent) : QWidget(parent), m_DirectionalLight(nullptr) {}

	void DirectionalLightWidget::SetDirectionalLight(pawn::engine::DirectionalLightComponent* directionalLight) {
		m_DirectionalLight = directionalLight;
	}

}
