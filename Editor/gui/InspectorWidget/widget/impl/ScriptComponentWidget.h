#pragma once


#include "PawnEngine/engine/components/ScriptComponent.h"

#include <QtWidgets/QWidget>
#include <QLabel>
#include <QLineEdit>

namespace editor {

	namespace impl {

		class ScriptComponentWidget : public QWidget {
			Q_OBJECT

			public:
				ScriptComponentWidget(QWidget* parent = Q_NULLPTR);

				void SetScript(pawn::engine::ScriptComponent* script);

				QLineEdit* GetScriptLineEdit() { return m_ScriptLineEdit; }

			signals:
				void ScriptModified();

			public slots:
				void OnLineEditPress();

			private:
				void InitConnections();

			private:
				pawn::engine::ScriptComponent* m_Script;

				QLineEdit* m_ScriptLineEdit;
				QLabel* m_ScriptLabel;
		};

	}

}
