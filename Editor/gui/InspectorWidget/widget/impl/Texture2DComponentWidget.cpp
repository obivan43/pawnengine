#include "Texture2DComponentWidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

namespace editor::impl {

	Texture2DComponentWidget::Texture2DComponentWidget(QWidget* parent)
		: QWidget(parent)
		, m_Entity(nullptr)
		, m_Texture2D(nullptr)
		, m_Color(nullptr)
		, m_Texture2DLineEdit(nullptr)
		, m_Texture2DLabel(nullptr) {

		QVBoxLayout* layout = new QVBoxLayout(this);

		QHBoxLayout* textureLayout = new QHBoxLayout();

		m_Color = new Double3Widget("Color", glm::vec3(0.0f), this);
		m_Color->SetMinMax(0.0, 1.0);

		m_Texture2DLineEdit = new QLineEdit(this);

		m_Texture2DLabel = new QLabel("Texture2D", this);
		m_Texture2DLabel->setMinimumWidth(80);

		textureLayout->addWidget(m_Texture2DLabel);
		textureLayout->addWidget(m_Texture2DLineEdit);

		layout->addWidget(m_Color);
		layout->addLayout(textureLayout);

		setLayout(layout);

		InitConnections();
	}

	void Texture2DComponentWidget::OnColorChanged(glm::vec3 value) {
		if (m_Texture2D) {
			m_Texture2D->Color = value;
		}
	}

	void Texture2DComponentWidget::SetEntity(pawn::engine::GameEntity* entity) {
		m_Entity = entity;
	}

	void Texture2DComponentWidget::SetTexture2D(pawn::engine::Texture2DComponent* texture2D) {
		m_Texture2D = texture2D;
		m_Texture2DLineEdit->setText(texture2D->TextureName.c_str());
		m_Color->SetValue(texture2D->Color);
	}

	void Texture2DComponentWidget::OnLineEditPress() {
		QString text{ m_Texture2DLineEdit->text() };

		std::string& textureName{ m_Texture2D->TextureName };
		textureName = text.toLocal8Bit().constData();

		emit Texture2DModified(*m_Entity);
		m_Texture2DLineEdit->clearFocus();
	}

	void Texture2DComponentWidget::InitConnections() {
		connect(
			m_Color,
			SIGNAL(ValueChanged(glm::vec3)),
			this, 
			SLOT(OnColorChanged(glm::vec3))
		);

		connect(
			m_Texture2DLineEdit,
			SIGNAL(returnPressed()),
			this,
			SLOT(OnLineEditPress())
		);
	}

}
