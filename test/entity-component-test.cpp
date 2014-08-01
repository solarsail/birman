#include <iostream>
#include <memory>
#include "any.hpp"
#include "components/component.hpp"
#include "componentfactory.hpp"
#include "entityfactory.hpp"

class TestComponent : public Component {
    public:
        void registerProperty() override
        {
            _entity->provideProperty("test", [this]() {
                    return this->getPosition();
            });
        }

    private:
        int getPosition() { return 3; }

};

int main()
{
    GameEntityFactory ef;
    ComponentFactory cf;

    auto e = ef.newEntity();
    auto c = cf.create<TestComponent>();
    e->attachComponent(c);
    Any a = e->getProperty("test");
    std::cout << a.as<int>() << std::endl;
    return 0;
}
