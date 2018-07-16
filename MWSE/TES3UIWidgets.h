#pragma once

#include "TES3UIElement.h"

namespace TES3 {
	namespace UI {
		struct WidgetFillbar : Element {
			int getCurrent() const;
			void setCurrent(int value);
			int getMax() const;
			void setMax(int value);
			bool getShowText() const;
			void setShowText(bool flag);
			void setFillColour(const float(&c)[3]);
			void setFillAlpha(float a);

			WidgetFillbar() = delete;
			static WidgetFillbar* fromElement(Element* e);
		private:
			static bool initProperties();
		};

		struct WidgetScrollBar : Element {
			int getCurrent() const;
			void setCurrent(int value);
			int getMax() const;
			void setMax(int value);
			int getStepX() const;
			void setStepX(int value);
			int getJumpX() const;
			void setJumpX(int value);

			WidgetScrollBar() = delete;
			static WidgetScrollBar* fromElement(Element* e);
		private:
			static bool initProperties();
		};

		struct WidgetTextInput : Element {
			int getLengthLimit() const;
			void setLengthLimit(int limit);
			bool getNoLimit() const;
			void setNoLimit(bool flag);
			bool getEraseOnFirstKey() const;
			void setEraseOnFirstKey(bool flag);

			WidgetTextInput() = delete;
			static WidgetTextInput* fromElement(Element* e);
		private:
			static bool initProperties();
		};

		struct WidgetTextSelect : Element {
			int getState() const;
			void setState(int state);
			void setColourIdle(const float(&c)[3]);
			void setColourOver(const float(&c)[3]);
			void setColourPressed(const float(&c)[3]);
			void setColourDisabled(const float(&c)[3]);
			void setColourDisabledOver(const float(&c)[3]);
			void setColourDisabledPressed(const float(&c)[3]);
			void setColourActive(const float(&c)[3]);
			void setColourActiveOver(const float(&c)[3]);
			void setColourActivePressed(const float(&c)[3]);

			WidgetTextSelect() = delete;
			static WidgetTextSelect* fromElement(Element* e);
		private:
			static bool initProperties();
		};
	}
}