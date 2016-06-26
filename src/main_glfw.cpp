#include <Magnum/Platform/GlfwApplication.h>
#include <Magnum/DefaultFramebuffer.h>
#include <Magnum/Renderer.h>
#include <Magnum/Timeline.h>

using namespace Magnum;
typedef Platform::GlfwApplication::KeyEvent KeyEvent;
typedef Platform::GlfwApplication::MouseEvent MouseEvent;
typedef Platform::GlfwApplication::MouseMoveEvent MouseMoveEvent;
typedef Platform::GlfwApplication::InputEvent InputEvent;

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
                       .setSize({400, 400})}
                       //.setWindowFlags(Configuration::WindowFlag::AllowHighDpi)}
{
    setSwapInterval(1);

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
            if( event.modifiers() & InputEvent::Modifier::AltGr )
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
    //return this->windowSize().x() != defaultFramebuffer.viewport().sizeX();
    return false;
}

void ScrollTest::mouseMoveEvent(MouseMoveEvent& event) {
    Vector2i pos = event.position();

    if( this->isRetina() ) {
        pos *= 2;
    }

    printf("Mouse Move event: (pos: <%d, %d>)\n", pos.x(), pos.y());

    // Ask Magnum to redraw us
    this->redraw();
}

void ScrollTest::mouseScrollEvent(MouseScrollEvent& event) {
    printf("Scroll event: %.2f, %.2f\n", event.offset().x(), event.offset().y());

    this->redraw();
}

MAGNUM_APPLICATION_MAIN(ScrollTest)
