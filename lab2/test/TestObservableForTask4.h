#pragma once
#include "../Observer/IObserver.h"

struct TestStructForTask4
{
    int id = 0;
    std::string name;
};

class TestObservableForTask4 final : public CObservable<TestStructForTask4>
{
protected:
    [[nodiscard]] TestStructForTask4 GetChangedData() const override
    {
        TestStructForTask4 data;
        data.id = 0;
        data.name = "Test";
        return data;
    }
};

class TestObserverForTask4 final : public IObserver<TestStructForTask4>
{
public:
    void Update(const IObservable<TestStructForTask4>& observable, const TestStructForTask4& data) override
    {
        m_onUpdate(observable);
    }

    void SetOnUpdate(const std::function<void(const IObservable<TestStructForTask4>&)>& onUpdate)
    {
        m_onUpdate = onUpdate;
    }

private:
    std::function<void(const IObservable<TestStructForTask4>&)> m_onUpdate = {};
};