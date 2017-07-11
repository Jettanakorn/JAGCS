#ifndef DESCRIPTION_VEHICLE_PRESENTER_H
#define DESCRIPTION_VEHICLE_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "db_traits.h"

namespace db
{
    class DbFacade;
}

namespace presentation
{
    class DescriptionVehiclePresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        DescriptionVehiclePresenter(db::DbFacade* facade, const db::VehiclePtr& vehicle,
                                    QObject* parent = nullptr);

        db::VehiclePtr vehicle() const;

    public slots:
        void updateView();
        void updateStatus();
        void save();
        void remove();

    protected:
        void connectView(QObject* view) override;

    private:
        db::DbFacade* const m_facade;
        db::VehiclePtr m_vehicle;
    };
}

#endif // DESCRIPTION_VEHICLE_PRESENTER_H
