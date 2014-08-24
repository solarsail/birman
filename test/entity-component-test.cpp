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
            _entity->notify("Test");
        }

        void registerProperties() override
        {
			_entity->provideProperty("Test", [this]() { return _value; }, [this](Any v) { this->setValue(v);  });
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
    auto e = GameEntityFactory::newEntity();
    auto rc = ComponentFactory::create<ReceiverComponent>();
    auto sc = ComponentFactory::create<SenderComponent>();
    e->attachComponent(sc);
    e->attachComponent(rc);
    sc->setValue(5);
    e->setProperty("Test", 6);
	getchar();
    return 0;
}
