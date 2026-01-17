#pragma once
#include "../Observer/IObserver.h"

struct TestStruct
{
    int id = 0;
    std::string name;
};

class TestObservable final : public CObservable<TestStruct>
{
protected:
    [[nodiscard]] TestStruct GetChangedData() const override
    {
        TestStruct data;
        data.id = 0;
        data.name = "Test";
        return data;
    }
};

class TestObserver final : public IObserver<TestStruct>
{
public:
    void Update(const IObservable<TestStruct>& observable, const TestStruct& data) override
    {
        m_onUpdate();
    }

    void SetOnUpdate(const std::function<void()>& onUpdate)
    {
        m_onUpdate = onUpdate;
    }

private:
    std::function<void()> m_onUpdate = {};
};