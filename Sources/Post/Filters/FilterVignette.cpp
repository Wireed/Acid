#include "FilterVignette.hpp"

namespace acid
{
	FilterVignette::FilterVignette(const GraphicsStage &graphicsStage, const float &innerRadius, const float &outerRadius, const float &opacity) :
		IPostFilter(graphicsStage, {"Shaders/Filters/Default.vert", "Shaders/Filters/Vignette.frag"}, {}),
		m_uniformScene(UniformHandler()),
		m_innerRadius(innerRadius),
		m_outerRadius(outerRadius),
		m_opacity(opacity)
	{
	}

	void FilterVignette::Render(const CommandBuffer &commandBuffer, const Vector4 &clipPlane, const ICamera &camera)
	{
		// Updates uniforms.
		m_uniformScene.Push("innerRadius", m_innerRadius);
		m_uniformScene.Push("outerRadius", m_outerRadius);
		m_uniformScene.Push("opacity", m_opacity);

		// Updates descriptors.
		m_descriptorSet.Push("UboScene", &m_uniformScene);
	//	m_descriptorSet.Push("writeColour", GetAttachment("writeColour", "resolved"));
	//	m_descriptorSet.Push("samplerColour", GetAttachment("samplerColour", "resolved"));
		PushConditional("writeColour", "samplerColour", "resolved", "diffuse");
		bool updateSuccess = m_descriptorSet.Update(m_pipeline);

		if (!updateSuccess)
		{
			return;
		}

		// Draws the object.
		m_pipeline.BindPipeline(commandBuffer);

		m_descriptorSet.BindDescriptor(commandBuffer);
		m_model->CmdRender(commandBuffer);
	}
}