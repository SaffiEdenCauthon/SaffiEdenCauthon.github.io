#ifndef ENGINE_MAINTENANCE_H
#define ENGINE_MAINTENANCE_H

#include <QDebug>
#include <QFileInfo>
#include <QObject>
#include <QSettings>
#include <QTimer>
#include <cmath>
#include <unistd.h>

#define SIX_MINS_IN_MS 360000
#define MS_IN_HR       3600000

class engine_maintenance : public QObject
{
    Q_PROPERTY(float eng_hrs      READ eng_hrs      WRITE set_eng_hrs      NOTIFY eng_hrs_changed)
    Q_PROPERTY(float eng_hrs_left READ eng_hrs_left WRITE set_eng_hrs_left NOTIFY eng_hrs_left_changed)
    Q_PROPERTY(float eng_hrs_this READ eng_hrs_this WRITE set_eng_hrs_this NOTIFY eng_hrs_this_changed)
    Q_PROPERTY(int   maint_missed READ maint_missed WRITE set_maint_missed NOTIFY maint_missed_changed)
    Q_PROPERTY(bool  eng_oil      READ eng_oil      WRITE set_eng_oil      NOTIFY eng_oil_changed)
    Q_PROPERTY(bool  eng_oil_fil  READ eng_oil_fil  WRITE set_eng_oil_fil  NOTIFY eng_oil_fil_changed)
    Q_PROPERTY(bool  eng_fuel_fil READ eng_fuel_fil WRITE set_eng_fuel_fil NOTIFY eng_fuel_fil_changed)
    Q_PROPERTY(bool  pump_oil     READ pump_oil     WRITE set_pump_oil     NOTIFY pump_oil_changed)
    Q_PROPERTY(bool  seal_change  READ seal_change  WRITE set_seal_change  NOTIFY seal_change_changed)
    Q_PROPERTY(bool  valve_change READ valve_change WRITE set_valve_change NOTIFY valve_change_changed)
    Q_PROPERTY(bool  is_eng_kill  READ is_eng_kill  WRITE set_is_eng_kill  NOTIFY is_eng_kill_changed)


    Q_OBJECT

    public:
    engine_maintenance();
    ~engine_maintenance();

    float eng_hrs() const;
    float eng_hrs_left() const;
    float eng_hrs_this() const;
    int   maint_missed() const;
    bool  eng_oil() const;
    bool  eng_oil_fil() const;
    bool  eng_fuel_fil() const;
    bool  pump_oil() const;
    bool  seal_change() const;
    bool  valve_change() const;
    bool  is_eng_kill() const;

    void set_is_eng_kill(const bool &v);
    bool needs_maintenance();

    QTimer *engine_hrs_timer;

    public slots:
    void handle_eng_hrs_timer(bool is_low_oil_pressure);
    void reset_flags();

    private:
    void set_eng_hrs(const float &v);
    void set_eng_hrs_left(const float &v);
    void set_eng_hrs_this(const float &v);
    void set_maint_missed(const int &v);
    void set_eng_oil(const bool &v);
    void set_eng_oil_fil(const bool &v);
    void set_eng_fuel_fil(const bool &v);
    void set_pump_oil(const bool &v);
    void set_seal_change(const bool &v);
    void set_valve_change(const bool &v);

    const QString SETTINGS_INI_FILE = "/opt/settings.ini";

    //Test Code
//    const int     TIME_FOR_TIMER_Q  = 500;
    //Production Code
    const int     TIME_FOR_TIMER_Q  = SIX_MINS_IN_MS;

    float _eng_hrs;
    float _eng_hrs_left;
    float _eng_hrs_this;
    int   _maint_missed;
    bool  _eng_oil;
    bool  _eng_oil_fil;
    bool  _eng_fuel_fil;
    bool  _pump_oil;
    bool  _seal_change;
    bool  _valve_change;
    bool  _is_eng_kill;

    private slots:
    void load_variables_from_disk();
    void save_variables_to_disk();
    void increase_eng_hrs();

    signals:
    void eng_hrs_changed();
    void eng_hrs_left_changed();
    void eng_hrs_this_changed();
    void maint_missed_changed();
    void eng_oil_changed();
    void eng_oil_fil_changed();
    void eng_fuel_fil_changed();
    void pump_oil_changed();
    void seal_change_changed();
    void valve_change_changed();
    void is_eng_kill_changed();
};

#endif // ENGINE_MAINTENANCE_H
