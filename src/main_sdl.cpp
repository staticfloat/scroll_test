#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/DefaultFramebuffer.h>
#include <Magnum/Renderer.h>
#include <Magnum/Timeline.h>

using namespace Magnum;
typedef Platform::Sdl2Application::KeyEvent KeyEvent;
typedef Platform::Sdl2Application::MouseEvent MouseEvent;
typedef Platform::Sdl2Application::MouseMoveEvent MouseMoveEvent;
typedef Platform::Sdl2Application::InputEvent InputEvent;

class ScrollTest: public Platform::Application {
    public:
        explicit ScrollTest(const Arguments& arguments);
        ~ScrollTest();

    private:
        bool isRetina();

        void drawEvent() override;
        void keyPressEvent(KeyEvent& event) override;
        void mouseMoveEvent(MouseMoveEvent& event) override;
        void mouseScrollEvent(MouseScrollEvent& event) override;
};




ScrollTest::ScrollTest(const Arguments& arguments):
    Platform::Application{arguments,
        Configuration{}.setTitle("ScrollTest v0.1.12d")
                       .setSize({400, 400})
                       .setWindowFlags(Configuration::WindowFlag::AllowHighDpi)}
{
    setSwapInterval(1);
    setMinimalLoopPeriod(10);

    // Kick our drawing off with a bang!
    this->redraw();
}

ScrollTest::~ScrollTest() {
}

void ScrollTest::drawEvent() {
    defaultFramebuffer.clear(FramebufferClear::Color);

    swapBuffers();
}

void ScrollTest::keyPressEvent(KeyEvent& event) {
    switch( event.key() ) {
        case KeyEvent::Key::W: {
            if( event.modifiers() & InputEvent::Modifier::Cmd )
                this->exit();
        }   break;
        default:
            break;
    }

    // We basically always need to redraw if someone presses a key.
    this->redraw();
    event.setAccepted();
}

bool ScrollTest::isRetina() {
    // We are highdpi if our window doesn't match our framebuffer
    return this->windowSize().x() != defaultFramebuffer.viewport().sizeX();
}

void ScrollTest::mouseMoveEvent(MouseMoveEvent& event) {
    Vector2i pos = event.position();
    Vector2i relpos = event.relativePosition();

    if( this->isRetina() ) {
        pos *= 2;
        relpos *= 2;
    }

    printf("Mouse Move event: (pos: <%d, %d>, relpos: <%d, %d>)\n", pos.x(), pos.y(), relpos.x(), relpos.y());

    // Ask Magnum to redraw us
    this->redraw();
}

void ScrollTest::mouseScrollEvent(MouseScrollEvent& event) {
    printf("Scroll event: %.2f, %.2f\n", event.offset().x(), event.offset().y());

    this->redraw();
}

MAGNUM_APPLICATION_MAIN(ScrollTest)
