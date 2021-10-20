#include "ScriptComponentWidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

namespace editor::impl {

	ScriptComponentWidget::ScriptComponentWidget(QWidget* parent)
		: QWidget(parent)
		, m_Script(nullptr)
		, m_ScriptLineEdit(nullptr)
		, m_ScriptLabel(nullptr) {

		QVBoxLayout* layout = new QVBoxLayout(this);

		QHBoxLayout* scriptLayout = new QHBoxLayout();

		m_ScriptLineEdit = new QLineEdit(this);

		m_ScriptLabel = new QLabel("Script", this);
		m_ScriptLabel->setMinimumWidth(80);

		scriptLayout->addWidget(m_ScriptLabel);
		scriptLayout->addWidget(m_ScriptLineEdit);

		layout->addLayout(scriptLayout);

		setLayout(layout);

		InitConnections();
	}

	void ScriptComponentWidget::SetScript(pawn::engine::ScriptComponent* script) {
		m_Script = script;
		m_ScriptLineEdit->setText(m_Script->FileName.c_str());
	}

	void ScriptComponentWidget::OnLineEditPress() {
		QString& text{ m_ScriptLineEdit->text() };

		m_Script->FileName = text.toLocal8Bit().constData();

		emit ScriptModified();
		m_ScriptLineEdit->clearFocus();
	}

	void ScriptComponentWidget::InitConnections() {
		connect(
			m_ScriptLineEdit,
			SIGNAL(returnPressed()),
			this,
			SLOT(OnLineEditPress())
		);
	}

}
