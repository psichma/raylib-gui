#pragma once
#include <raylib.h>

namespace psgui::graphics {
	class Shape {
		protected:
			Vector2 position;
			Vector2 size;
			Color fill_color;
			Color outline_color;
			float outline_thickness;
			bool draw_outline;

			Vector2 origin;
			float rotation;

			virtual void init();

		public:
			Shape();
			Shape(float x, float y);
			Shape(float x, float y, float width, float height);
			Shape(Vector2 position);
			Shape(Vector2 position, Vector2 size);
			virtual ~Shape();

			virtual void setPosition(float x, float y);
			virtual void setPosition(Vector2 position);
			virtual Vector2 getPosition() {return this->position;}

			virtual void setSize(Vector2 size);
			virtual void setSize(float x, float y);
			virtual Vector2 getSize() {return this->size;}

			virtual void setWidth(float w);
			virtual float getWidth() {return this->size.x;}
			virtual void setHeight(float h);
			virtual float getHeight() {return this->size.y;}

			virtual void setFillColor(Color color);
			Color getFillColor() {return this->fill_color;}

			virtual void setOutlineColor(Color color);
			Color getOutlineColor() {return this->outline_color;}

			void setOutlineThickness(float thickness);
			float getOutlineThickness() {return this->outline_thickness;}
			void setOutline(bool state);
			void toggleOutline();

			void setRotation(float rotation);
			float getRotation() {return this->rotation;}

			virtual void update(float delta) = 0;
			virtual void render() const = 0;
	};
}
