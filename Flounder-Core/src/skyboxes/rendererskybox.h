#pragma once

#include "../renderer/irenderer.h"

#include "skyboxes.h"

namespace flounder
{
	class rendererskybox :
		public irenderer
	{
	private:
		shader *m_shader;
	public:
		rendererskybox();

		~rendererskybox();

		void render(const vector4 &clipPlane, const icamera &camera) override;
	private:
		void prepareRendering(const vector4 &clipPlane, const icamera &camera);

		void renderSkybox(skyboxes *object);

		void endRendering();
	};
}