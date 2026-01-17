#pragma once

#include <map>
#include <set>

template <typename T>
class IObserver;

template <typename T>
class IObservable;

template <class T>
class CObservable;

template <typename T>
class IObserver
{
public:
    virtual void Update(const IObservable<T>& observable, const T& data) = 0;
    virtual ~IObserver() = default;
};

template <typename T>
class IObservable
{
public:
    virtual ~IObservable() = default;
    virtual void RegisterObserver(IObserver<T>& observer, int priority) = 0;
    virtual void NotifyObservers() = 0;
    virtual void RemoveObserver(IObserver<T>& observer) = 0;
};

template <class T>
class CObservable : public IObservable<T>
{
public:
    typedef IObserver<T> ObserverType;

    void RegisterObserver(ObserverType& observer, const int priority) override
    {
        m_observers.insert({priority, &observer});
    }

    void NotifyObservers() override
    {
        T data = GetChangedData();
        m_notifying = true;

        for (auto observersCopy = m_observers; const auto& pair : observersCopy)
        {
            if (m_onRemoveObservers.contains(pair.second))
            {
                continue;
            }
            pair.second->Update(*this, data);
        }
        m_notifying = false;
        ProceedOnRemoveObservers();
    }

    void RemoveObserver(ObserverType& observer) override
    {
        if (m_notifying)
        {
            m_onRemoveObservers.insert(&observer);
        }
        else
        {
            RemoveObserverImpl(&observer);
        }
    }

    [[nodiscard]] int GetObserverCount() const
    {
        return m_observers.size();
    }

protected:
    virtual T GetChangedData() const = 0;

private:
    std::multimap<
        int,
        ObserverType*,
        std::greater<int>
    > m_observers;
    std::set<ObserverType*> m_onRemoveObservers;
    bool m_notifying = false;

    void RemoveObserverImpl(ObserverType* observer)
    {
        for (auto it = m_observers.begin(); it != m_observers.end(); ++it)
        {
            if (it->second == observer)
            {
                m_observers.erase(it);
                return;
            }
        }
    }

    void ProceedOnRemoveObservers()
    {
        for (const auto& observer : m_onRemoveObservers)
        {
            RemoveObserverImpl(observer);
        }
        m_onRemoveObservers.clear();
    }
};