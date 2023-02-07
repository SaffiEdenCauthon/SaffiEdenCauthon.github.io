#include "engine_maintenance.h"

engine_maintenance::engine_maintenance()
{
    engine_hrs_timer = new QTimer(this);
    QObject::connect(engine_hrs_timer, SIGNAL(timeout()), this, SLOT(increase_eng_hrs()));
    QObject::connect(this, SIGNAL(is_eng_kill_changed()), this, SLOT(save_variables_to_disk()));

    _eng_hrs      = 0.0;
    _eng_hrs_left = 525.0;
    _eng_hrs_this = 0.0;
    _maint_missed = 0;
    _eng_oil      = false;
    _eng_oil_fil  = false;
    _eng_fuel_fil = false;
    _pump_oil     = false;
    _seal_change  = false;
    _valve_change = false;
    _is_eng_kill  = false;

    load_variables_from_disk();

    handle_eng_hrs_timer(false);
}
engine_maintenance::~engine_maintenance()
{
    delete engine_hrs_timer;
}

float engine_maintenance::eng_hrs() const
{
    return _eng_hrs;
}
float engine_maintenance::eng_hrs_left() const
{
    return _eng_hrs_left;
}
float engine_maintenance::eng_hrs_this() const
{
    return _eng_hrs_this;
}
int engine_maintenance::maint_missed() const
{
    return _maint_missed;
}
bool  engine_maintenance::eng_oil() const
{
    return _eng_oil;
}
bool  engine_maintenance::eng_oil_fil() const
{
    return _eng_oil_fil;
}
bool  engine_maintenance::eng_fuel_fil() const
{
    return _eng_fuel_fil;
}
bool  engine_maintenance::pump_oil() const
{
    return _pump_oil;
}
bool  engine_maintenance::seal_change() const
{
    return _seal_change;
}
bool  engine_maintenance::valve_change() const
{
    return _valve_change;
}
bool  engine_maintenance::is_eng_kill() const
{
    return _is_eng_kill;
}
void  engine_maintenance::set_eng_hrs(const float &v)
{
    if (v != _eng_hrs)
    {
        _eng_hrs = v;
//        qDebug() << "Eng Hrs: "      << eng_hrs();
        emit eng_hrs_changed();
    }
}
void  engine_maintenance::set_eng_hrs_left(const float &v)
{
    if (v != _eng_hrs_left)
    {
        _eng_hrs_left = v;
        qDebug() << "Eng Hrs Left: " << eng_hrs_left();
        emit eng_hrs_left_changed();
    }
}
void  engine_maintenance::set_eng_hrs_this(const float &v)
{
    if (v != _eng_hrs_this)
    {
        _eng_hrs_this = v;
        qDebug() << "Eng Hrs This: " << eng_hrs_this();
        emit eng_hrs_this_changed();
    }
}
void  engine_maintenance::set_maint_missed(const int &v)
{
    if (v != _maint_missed)
    {
        _maint_missed = v;
        qDebug() << "Maintenance Sessions Missed: " << maint_missed();
        emit maint_missed_changed();
    }
}
void  engine_maintenance::set_eng_oil(const bool &v)
{
    if (v != _eng_oil)
    {
        _eng_oil = v;
//        qDebug() << "Eng Oil Light: " << eng_oil();
        emit eng_oil_changed();
    }
}
void  engine_maintenance::set_eng_oil_fil(const bool &v)
{
    if (v != _eng_oil_fil)
    {
        _eng_oil_fil = v;
//        qDebug() << "Eng Oil Filter Light: " << eng_oil_fil();
        emit eng_oil_fil_changed();
    }
}
void  engine_maintenance::set_eng_fuel_fil(const bool &v)
{
    if (v != _eng_fuel_fil)
    {
        _eng_fuel_fil = v;
//        qDebug() << "Eng Fuel Filter Light: " << eng_fuel_fil();
        emit eng_fuel_fil_changed();
    }
}
void  engine_maintenance::set_pump_oil(const bool &v)
{
    if (v != _pump_oil)
    {
        _pump_oil = v;
//        qDebug() << "Pump Oil Light: " << pump_oil();
        emit pump_oil_changed();
    }
}
void  engine_maintenance::set_seal_change(const bool &v)
{
    if (v != _seal_change)
    {
        _seal_change = v;
//        qDebug() << "Seal Change Light: " << seal_change();
        emit seal_change_changed();
    }
}
void  engine_maintenance::set_valve_change(const bool &v)
{
    if (v != _valve_change)
    {
        _valve_change = v;
//        qDebug() << "Valve Change Light: " << valve_change();
        emit valve_change_changed();
    }
}
void  engine_maintenance::set_is_eng_kill(const bool &v)
{
    if (v != _is_eng_kill)
    {
        _is_eng_kill = v;
        emit is_eng_kill_changed();
    }
}
bool  engine_maintenance::needs_maintenance()
{
    return eng_oil()  || eng_oil_fil() || eng_fuel_fil() ||
           pump_oil() || seal_change() || valve_change();
}
void  engine_maintenance::handle_eng_hrs_timer(bool is_low_oil_pressure)
{
    if (is_low_oil_pressure)
    {
        engine_hrs_timer->stop();
    }
    else
    {
        engine_hrs_timer->start(TIME_FOR_TIMER_Q);
    }
}
void  engine_maintenance::reset_flags()
{
    set_eng_oil     (false);
    set_eng_oil_fil (false);
    set_eng_fuel_fil(false);
    set_pump_oil    (false);
    set_seal_change (false);
    set_valve_change(false);

    set_maint_missed(0);
}
void  engine_maintenance::load_variables_from_disk()
{
    QFileInfo file_to_check(SETTINGS_INI_FILE);

    if (file_to_check.exists() && file_to_check.isFile())
    {
        QSettings settings(SETTINGS_INI_FILE, QSettings::IniFormat);

        settings.beginGroup("General");
        set_eng_hrs     (settings.value("eng_hrs"     ,     0).toFloat());
        set_eng_hrs_left(settings.value("eng_hrs_left",   525).toFloat());
        set_eng_hrs_this(settings.value("eng_hrs_this",     0).toFloat());
        set_maint_missed(settings.value("maint_missed",     0).toInt());
        set_eng_oil     (settings.value("eng_oil"     , false).toBool());
        set_eng_oil_fil (settings.value("eng_oil_fil" , false).toBool());
        set_eng_fuel_fil(settings.value("eng_fuel_fil", false).toBool());
        set_pump_oil    (settings.value("pump_oil"    , false).toBool());
        set_seal_change (settings.value("seal_change" , false).toBool());
        set_valve_change(settings.value("valve_change", false).toBool());
        set_is_eng_kill (settings.value("is_eng_kill" , false).toBool());
        settings.endGroup();
    }
}
void  engine_maintenance::save_variables_to_disk()
{
    QSettings settings(SETTINGS_INI_FILE, QSettings::IniFormat);

    settings.beginGroup("General");
    settings.setValue("eng_hrs"     , eng_hrs     ());
    settings.setValue("eng_hrs_left", eng_hrs_left());
    settings.setValue("eng_hrs_this", eng_hrs_this());
    settings.setValue("maint_missed", maint_missed());
    settings.setValue("eng_oil"     , eng_oil     ());
    settings.setValue("eng_oil_fil" , eng_oil_fil ());
    settings.setValue("eng_fuel_fil", eng_fuel_fil());
    settings.setValue("pump_oil"    , pump_oil    ());
    settings.setValue("seal_change" , seal_change ());
    settings.setValue("valve_change", valve_change());
    settings.setValue("is_eng_kill" , is_eng_kill ());
    settings.sync();
    settings.endGroup();
    sync();
}
void  engine_maintenance::increase_eng_hrs()
{
    //Test Code
//    set_eng_hrs(eng_hrs() + 5);

    //Production Code
    set_eng_hrs(eng_hrs() + ((float)TIME_FOR_TIMER_Q/MS_IN_HR));

    if (eng_hrs() >= 525.0)
    {
        if (fmod((eng_hrs() - 25), 500.0) == 0)
        {
            set_maint_missed(maint_missed() + 1);

            set_eng_oil     (true);
            set_eng_oil_fil (true);
            set_eng_fuel_fil(true);
            set_pump_oil    (true);
        }

        if (fmod((eng_hrs() - 25), 3000.0) == 0)
        {
            set_seal_change(true);
        }
        else if (fmod((eng_hrs() - 25), 1500.0) == 0)
        {
            set_valve_change(true);
        }

        set_eng_hrs_left(500.0 - fmod((eng_hrs() - 25), 500.0));
        set_eng_hrs_this(-1 * ((500.0 - eng_hrs_left()) + ((maint_missed() - 1) * 500)));
    }
    else
    {
        set_eng_hrs_left(525.0 - eng_hrs());
        set_eng_hrs_this(eng_hrs_left());
    }

    save_variables_to_disk();
}
