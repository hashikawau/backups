

#include "awt\Container.h"





//===========================================================
//===========================================================
class TestContainer:
    public Container
{
    class Listener:
        public ComponentListener,
        public FocusListener,
        public KeyListener,
        public MouseListener,
        public MouseMotionListener,
        public MouseWheelListener
    {
    public:
        virtual void componentHidden(ComponentEvent& e)
        {
            TestContainer* c
                = static_cast<TestContainer*>(e.getSource());
            c->_string = L"CHidden";
            c->repaint();
        }
        virtual void componentMoved(ComponentEvent& e)
        {
            TestContainer* c
                = static_cast<TestContainer*>(e.getSource());
            c->_string = L"CMoved";
            c->repaint();
        }
        virtual void componentResized(ComponentEvent& e)
        {
            TestContainer* c
                = static_cast<TestContainer*>(e.getSource());
            c->_string = L"CResized";
            c->repaint();
        }
        virtual void componentShown(ComponentEvent& e)
        {
            TestContainer* c
                = static_cast<TestContainer*>(e.getSource());
            c->_string = L"CShown";
            c->repaint();
        }
        virtual void focusGained(FocusEvent& e)
        {
            TestContainer* c
                = static_cast<TestContainer*>(e.getSource());
            c->_string = L"FGained";
            c->_string = String(c->_count +=1000);
            c->repaint();
        }
        virtual void focusLost(FocusEvent& e)
        {
            TestContainer* c
                = static_cast<TestContainer*>(e.getSource());
            c->_string = L"FLost";
            c->repaint();
        }
        virtual void keyPressed(KeyEvent& e)
        {
            TestContainer* c
                = static_cast<TestContainer*>(e.getSource());
            c->_string = String(c->_count +=100);
            c->_string = L"KPressed";
            c->repaint();
        }
        virtual void keyReleased(KeyEvent& e)
        {
            TestContainer* c
                = static_cast<TestContainer*>(e.getSource());
            c->_string = L"KReleased";
            c->repaint();
        }
        virtual void keyTyped(KeyEvent& e)
        {
            TestContainer* c
                = static_cast<TestContainer*>(e.getSource());
            c->_string = L"KTyped";
            c->_string = String(e.getKeyChar());
            c->repaint();
        }
        virtual void mouseClicked(MouseEvent& e)
        {
            TestContainer* c
                = static_cast<TestContainer*>(e.getSource());
            c->_string = L"MClicked";
            c->_bkcolor = -c->_bkcolor -1;
            c->setBackground(Color(c->_bkcolor));
            c->repaint();
        }
        virtual void mouseEntered(MouseEvent& e)
        {
            TestContainer* c
                = static_cast<TestContainer*>(e.getSource());
            c->_string = L"MEntered";
            c->_string = String(c->_count +=10);
            c->repaint();
        }
        virtual void mouseExited(MouseEvent& e)
        {
            TestContainer* c
                = static_cast<TestContainer*>(e.getSource());
            c->_string = L"MExited";
            c->repaint();
        }
        virtual void mousePressed(MouseEvent& e)
        {
            TestContainer* c
                = static_cast<TestContainer*>(e.getSource());
            c->_string = L"MEntered";
            c->_string = String(++c->_count);
            c->repaint();
        }
        virtual void mouseReleased(MouseEvent& e)
        {
            TestContainer* c
                = static_cast<TestContainer*>(e.getSource());
            c->_string = L"MReleased";
            c->repaint();
        }
        virtual void mouseDragged(MouseEvent& e)
        {
            TestContainer* c
                = static_cast<TestContainer*>(e.getSource());
            c->_string = L"MDragged";
            
            int x = c->getX();
            int y = c->getY();
            c->setLocation(
                x +e.getX() -c->_x,
                y +e.getY() -c->_y
            );
            c->repaint();
        }
        virtual void mouseMoved(MouseEvent& e)
        {
            TestContainer* c
                = static_cast<TestContainer*>(e.getSource());
            c->_string = L"MMoved";
            c->_x = e.getX();
            c->_y = e.getY();
            c->repaint();
        }
        virtual void mouseWheelMoved(MouseWheelEvent& e)
        {
            TestContainer* c
                = static_cast<TestContainer*>(e.getSource());
            c->_string = L"MWheelMoved";
            c->_string = L"ContainerMWheelMoved";
            c->_string = String(++c->_count);
            c->repaint();
        }
    };
    
    class TestComponent: public Component
    {
    public:
        class Listener:
            public MouseListener,
            public MouseMotionListener,
            public MouseWheelListener
        {
        public:
            virtual void mouseClicked(MouseEvent& e)
            {
                TestComponent* c
                    = static_cast<TestComponent*>(e.getSource());
                c->_string = String(++c->_count);
                c->_string = L"ComponentMClicked";
                c->repaint();
            }
            virtual void mouseEntered(MouseEvent& e){}
            virtual void mouseExited(MouseEvent& e){}
            virtual void mousePressed(MouseEvent& e){}
            virtual void mouseReleased(MouseEvent& e){}
            virtual void mouseDragged(MouseEvent& e)
            {
                TestComponent* c
                    = static_cast<TestComponent*>(e.getSource());
                c->_string = L"MDragged";
                c->_string =
                    String(L"x= ")
                    + String(c->_x)
                    + L", y= "
                    + String(c->_y);
                
                const Container& parent = c->getParent();
                c->_mousex = e.getX();
                c->_mousey = e.getY();
                c->_newx += c->_mousex -c->_x;
                c->_newy += c->_mousey -c->_y;
                c->setLocation(
                    c->_newx,
                    c->_newy
                );
                c->repaint();
                c->getParent().repaint();
            }
            virtual void mouseMoved(MouseEvent& e)
            {
                TestComponent* c
                    = static_cast<TestComponent*>(e.getSource());
                c->_x = e.getX();
                c->_y = e.getY();
                const Container& parent = c->getParent();
                c->_newx = c->getX() -parent.getX();
                c->_newy = c->getY() -parent.getY();
                c->_string = String(L"x= ") +String(c->_x) +L", y= " +String(c->_y);
                c->repaint();
                c->getParent().repaint();
            }
            virtual void mouseWheelMoved(MouseWheelEvent& e)
            {
                TestComponent* c
                    = static_cast<TestComponent*>(e.getSource());
                c->_string = L"MWheelMoved";
                c->_string = L"ComponentMWheelMoved";
                c->_string = String(c->getY());
                c->repaint();
            }
        };
        int _count;
        int _x;
        int _y;
        int _newx;
        int _newy;
        int _mousex;
        int _mousey;
        String _string;
        TestComponent(): _count(0), _x(0), _y(0){}
        virtual void paint(Graphics& g)
        {
            g.drawString(_string, 2, 2);
            g.drawRect(0, 0, getWidth(), getHeight());
        }
    };
    
friend class Listener;
friend class TestComponent::Listener;

private:
    int _x;
    int _y;
    int _width;
    int _height;
    int _numrow;
    int _numcol;
    int _bkcolor;
    String _string;
    int _count;
    
public:
    TestContainer(int count =0):
        _x(0),
        _y(0),
        _width(280),
        _height(200),
        _numrow(10),
        _numcol(5),
        _bkcolor(0x00FFFFFF),
        _string(static_cast<int>(this)),
        _count(count)
    {}
    
    
    virtual void paint(Graphics& g)
    {
        g.drawString(_string, 2, 2);
        g.drawRect(0, 0, getWidth(), getHeight());
        g.drawString(String(L"x= ") +String(getX()) +L", y= " +String(getY()), 2, 20);
        
        TestComponent* t = static_cast<TestComponent*>(&getComponent(0));
        g.drawString(String(L"x= ") +String(t->getX()) +L", y= " +String(t->getY()), 2, 40);
        g.drawString(String(L"_x= ") +String(t->_x) +L", _y= " +String(t->_y), 2, 60);
        g.drawString(String(L"newx= ") +String(t->_newx) +L", newy= " +String(t->_newy), 2, 80);
        g.drawString(String(L"mousex= ") +String(t->_mousex) +L", mousey= " +String(t->_mousey), 2, 100);
        //g.drawString(String((int)t) +L"  " + _numcol, 2, 60);
    }
    
    void teststart()
    {
        setBounds(50, 50, 300, 400);
        
        TestComponent* t = new TestComponent();
        t->setBounds(30, 150, 180, 20);
        TestContainer::TestComponent::Listener* tl = new TestContainer::TestComponent::Listener();
        t->addMouseListener(*tl);
        t->addMouseMotionListener(*tl);
        t->addMouseWheelListener(*tl);
        add(*t);
        
        _numcol = (int)t;
        TestContainer::Listener* l = new TestContainer::Listener();
        addMouseListener(*l);
        addMouseMotionListener(*l);
        addMouseWheelListener(*l);
        setVisible(true);
    }
};
//===========================================================
//===========================================================


//===========================================================
//===========================================================
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   PSTR lpCmdLine,
                   int nCmdShow)
{
    wchar_t programname[MAX_PATH +1];
    GetModuleFileNameW(0, programname, MAX_PATH);
    TestContainer test;
    test.teststart();
    
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return msg.wParam;
}
