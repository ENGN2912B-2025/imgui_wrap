//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#include <gui/gl/gl.h>
#include <gui/gui.hpp>
#include <gui/gl/FrameBuffer.hpp>

#include <cassert>

class TopFrame : public gui::ChildFrame
{
  gui::gl::FrameBuffer* frameBuffer_;
public:
  TopFrame() : frameBuffer_{ nullptr }
  {
  }

  void render() override
  {
    ImGui::Text("Top Frame");

    if (!frameBuffer_)
    {
      frameBuffer_ = new gui::gl::FrameBuffer();
    }

    frameBuffer_->setSize(gui::make<gui::Vec2i>(ImGui::GetContentRegionAvail()));

		ImGui::Image(
      (ImTextureID)(intptr_t)frameBuffer_->getTexture(),
			frameBuffer_->getSize().to<float>(),
			ImVec2(0, 1),
			ImVec2(1, 0)
		);

    drawGL();
  }

  void drawGL()
  {
    if (frameBuffer_ != nullptr)
    {
      frameBuffer_->bind();

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

      configureViewport(-1, 1, -1 , 1);
      glLoadIdentity();

      drawTriangle();

      frameBuffer_->unbind();
    }
  }

  void configureViewport(int x1, int y1, int x2, int y2)
  {
    assert(frameBuffer_ != nullptr);

    //make the viewport occupy the whole canvas
    const gui::Vec2i& canvasSize{ frameBuffer_->getSize() };
    glViewport(0, 0, canvasSize.x, canvasSize.y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //set the projection transformation
    glOrtho(x1, x2, y1, y2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  }

  void drawTriangle()
  {
    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0); glVertex3f(-0.6, -0.75, 0.5);
    glColor3f(0, 1, 0); glVertex3f(0.6, -0.75, 0);
    glColor3f(0, 0, 1); glVertex3f(0, 0.75, 0);
    glEnd();
  }
};

class BottomFrame : public gui::ChildFrame
{
public:
  void render() override
  {
    ImGui::Text("Bottom Frame");
  }
};

class LeftFrame : public gui::ChildFrame
{
public:
  void render() override
  {
    ImGui::Text("Left Frame");
  }
};

class MainWindow : public gui::Frame
{
  TopFrame topFrame_;
  BottomFrame bottomFrame_;
  LeftFrame leftFrame_;
public:
  void render() override
  {
    gui::VerticalSizer verticalSizer;

    verticalSizer.addChild(&topFrame_, 3);
    verticalSizer.addChild(&bottomFrame_);

    gui::HorizontalSizer horizontalSizer;
    horizontalSizer.addWithFixedSize(&leftFrame_, 200);
    horizontalSizer.addChild(&verticalSizer, 3);

    horizontalSizer.setSize(getContentSize());
    horizontalSizer.setPosition(getContentMin());
    horizontalSizer.draw();
  }
};

int main(int argc, char** argv)
{
  // Create the application
  gui::Application app{ "GUI: Hello GL!" };

  // Create the main window
  MainWindow mainWindow;

  // Run the application
  app.run();

  return 0;
}
