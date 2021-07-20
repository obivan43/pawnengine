#pragma once

#include "glm.hpp"

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QDoubleSpinBox>

namespace editor {

	namespace impl {

		class Double3Widget : public QWidget {
				Q_OBJECT

			public:
				Double3Widget(const QString& label, glm::vec3 value = glm::vec3(0.0f), QWidget* parent = Q_NULLPTR);

				void SetValue(glm::vec3 value);

			private:
				void InitConnections();

			private slots:
				void OnXChanged(double value);
				void OnYChanged(double value);
				void OnZChanged(double value);

			signals:
				void ValueChanged(glm::vec3);

			private:
				QLabel* m_Label;
				QDoubleSpinBox* m_X;
				QDoubleSpinBox* m_Y;
				QDoubleSpinBox* m_Z;
				glm::vec3 m_ValueCache;
		};

	}

}