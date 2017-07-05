#ifndef ABSTRACT_MAP_PRESENTER_H
#define ABSTRACT_MAP_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace presentation
{
    class AbstractMapPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        AbstractMapPresenter(QObject* object = nullptr);

        virtual double centerLatitude() const = 0;
        virtual double centerLongitude() const = 0;
        virtual float zoomLevel() const = 0;

    public slots:
        virtual void setMapCenter(double latitude, double longitude) = 0;
        virtual void setZoomLevel(float zoomLevel) = 0;
        void saveViewPort();

    protected:
        void connectView(QObject* view) override;
        void disconnectView(QObject *view) override;
    };
}

#endif // ABSTRACT_MAP_PRESENTER_H
