// Navigation pane project template
#ifndef Trail_HPP_
#define Trail_HPP_

#include <QObject>

namespace bb { namespace cascades { class Application; }}

/*!
 * @brief Application pane object
 *
 *Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class Trail : public QObject
{
    Q_OBJECT
public:
    Trail(bb::cascades::Application *app);
    virtual ~Trail() {}
};

#endif /* Trail_HPP_ */