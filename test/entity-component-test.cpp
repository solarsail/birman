#include <iostream>
#include <memory>
#include "any.hpp"
#include "components/component.hpp"
#include "componentfactory.hpp"
#include "entityfactory.hpp"

class SenderComponent : public Component {
    public:
        void setValue(int value)
        {
            _value = value;
            std::cout << "New value set in SenderComponent: " << value << std::endl;
            _entity->notify("Test", _value);
        }

    private:
        int _value;
};

class ReceiverComponent : public Component {
    public:
        void bindListeners() override
        {
            _entity->listen("Test", [](int value) { std::cout << "New value received in ReceiverComponent: " << value << std::endl; });
        }
};

int main()
{
    GameEntityFactory ef;
    ComponentFactory cf;

    auto e = ef.newEntity();
    auto rc = cf.create<ReceiverComponent>();
    auto sc = cf.create<SenderComponent>();
    e->attachComponent(sc);
    e->attachComponent(rc);
    sc->setValue(5);
    return 0;
}
