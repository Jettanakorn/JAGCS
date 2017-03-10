#include "domain_entry.h"

// Qt
#include <QScopedPointer>
#include <QDebug>

// Internal
#include "db_manager.h"

#include "settings_provider.h"

#include "mission_service.h"
#include "vehicle_service.h"
#include "abstract_vehicle.h"

#include "mavlink_communicator.h"
#include "mavlink_communicator_factory.h"

#include "proxy_manager.h"

#include "endpoint.h"

using namespace domain;

class DomainEntry::Impl
{
public:
    data_source::DbManager dbManager;

    VehicleService vehicleService;
    MissionService missionService;
    ProxyManager proxyManager;

    QScopedPointer<MavLinkCommunicator> communicator;
};

DomainEntry::DomainEntry():
    d(new Impl())
{
    qRegisterMetaType<Endpoint>("Endpoint");
    qRegisterMetaType<EndpointList>("EndpointList");

    qDebug() << d->dbManager.open("jagcs.sqlite");

    QObject::connect(&d->vehicleService, &VehicleService::vehicleAdded,
                     &d->missionService, &MissionService::addVehiclesMision);

    MavLinkCommunicatorFactory factory(&d->vehicleService, &d->missionService);
    d->communicator.reset(factory.create());
}

DomainEntry::~DomainEntry()
{
    delete d;
}

AbstractCommunicator* DomainEntry::communicator() const
{
    return d->communicator.data();
}

VehicleService* DomainEntry::vehicleService() const
{
    return &d->vehicleService;
}

MissionService* DomainEntry::missionService() const
{
    return &d->missionService;
}

ProxyManager* DomainEntry::proxyManager() const
{
    return &d->proxyManager;
}
