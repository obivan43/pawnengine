#pragma once

#include "Editor/editor/impl/EngineManager.h"

#include <memory>
#include <QWidget>

namespace editor {

	class EnvironmentWidget : public QWidget {
			Q_OBJECT

		public:
			static EnvironmentWidget* CreateImpl(QWidget* parent = Q_NULLPTR);

			virtual void RefreshPanel() = 0;

			void SetEngineManager(std::shared_ptr<impl::EngineManager>& engineManager);

			std::shared_ptr<impl::EngineManager> GetEngineManager();

		protected:
			EnvironmentWidget(QWidget* parent);

		protected:
			std::shared_ptr<impl::EngineManager> m_EngineManager;
	};

}
