---
layout: page
title: Common Practices
description: Showcase of Common Practices
img: assets/img/projects/work_03/blurred_img.png
importance: 3
category: work
---

### Project Description & Overview

> I commonly work with several clients to create embedded systems that interface with engine chassis. These projects often differ in complexity but remain remarkably similar.

I was solely responsible for integrating full-stack solutions and technologies for many of these projects. However, I have also worked collaboratively with several key stakeholders and outside engineering departments to ensure a quality standard that I hold close to heart.

Common core competencies for a common-practice project include developing network architecture, any UX/UI or label design, system programming, and the development of system software requirement specifications or other product documentation and manuals.

Common practice includes my introduction to the project after the salesperson receives a lead  and has had the chance to walk a customer through a sample configuration document.

<div class="row">
    <div class="col-sm mt-3 mt-md-0">
        {% include figure.html path="assets/img/projects/work_03/EXCEL_2023-02-07_12-33-11.png" title="Saleperson Configuration Document" class="img-fluid rounded z-depth-1" %}
    </div>
</div>
<div class="caption">
    A documented example of a salesperson's initial configuration document for a company labeled <code>CENSORED</code>.
</div>

***

### Showcase: Starting a Project

From the salesperson’s example, we can see that documentation for the project is off to a *fantastic* start. That is where communication with key stakeholders and the creation, and review, of a scope of work occurs. Often, I would assist in reviewing these pieces of documentation with my coworkers to ensure company success.

After reviewing the initial documentation proposed by the salesperson, creating formal documentation within relevant software files and developing any external documentation for stakeholders would be produced.

{% raw %}
```c
//------------------------------------------------------------------------------
/// \file     user_code.c
/// \brief    user code
/// \author   Saffi Kelley Kieffer, Senior Software Engineer, OPS Controls
/// \date     05.01.2023 (dd/mm/yy)
/// \version  4.00.00.01
/// \module   1.041.301.1000 - WPP
/// \project  [CENSORED]-[CENSORED]
//
/// \controller_01_io
//  Function Name       Connector   Action              REF
//  lvl_flt_mV          B6          IN_VOLTAGE_10       AI0
//  pto_01              C3          OUT_DIGITAL_CSO     DO_PWM0
//  blw_vac             C2          OUT_DIGITAL_CSO     DO_PWM1
//  blw_psi             C1          OUT_DIGITAL_CSO     DO_PWM2
//  valve_01_open       B1          OUT_DIGITAL_CSO     DO_PWM3
//  reel_left           B8          OUT_DIGITAL_CSO     DO_PWM4
//  reel_right          C8          OUT_DIGITAL_CSO     DO_PWM5
//  accel               C7          OUT_DIGITAL_CSO     DO_OUT0
//  decel               C6          OUT_DIGITAL_CSO     DO_OUT1
//
/// \controller_02_io
//  Function Name       Connector   Action              REF
//  hose_in             C6          OUT_DIGITAL_CSO     DO_PWM0
//  hose_out            C3          OUT_DIGITAL_CSO     DO_PWM1
//  spare_01_mom        C2          OUT_DIGITAL_CSO     DO_PWM2
//  spare_02_mom        C1          OUT_DIGITAL_CSO     DO_PWM3
//  spare_03_latch      B1          OUT_DIGITAL_CSO     DO_PWM4
//  spare_04_latch      B8          OUT_DIGITAL_CSO     DO_PWM5
//  valve_02_open       C8          OUT_DIGITAL_CSO     DO_OUT0
//------------------------------------------------------------------------------
```
{% endraw %}
<div class="caption">
    An example showing an excerpt of documentation within a <code>.C</code> code file
</div>

This documentation includes documenting network data, IO requirements (voltage, current limitations), wire harnessing lengths, and connector information. From this, I would work alongside my colleagues to determine the most appropriate and cost-effective solution to propose for the customer.

<div class="row">
    <div class="col-sm mt-3 mt-md-0">
        {% include figure.html path="assets/img/projects/work_03/EXCEL_2023-02-07_12-33-45.png" title="Initial Documentation" class="img-fluid rounded z-depth-1" %}
    </div>
</div>
<div class="caption">
    A documented example of a spreadsheet I developed outlying information for key stakeholders
</div>

***

### Showcase: Developing a Project in C

Following customer approval, I would start the development of core system components. These could often be implemented with minimal code.

> At past employers, we offered the benefits of both waterfall and agile software development methodologies. These simple projects often followed waterfall development techniques as they did not meet complexity requirements.

This project used <code>C</code> and <code>proprietary embedded systems</code> to satisfy customer demands.

{% raw %}
```c
void kp_2400_set_var(struct Keypad_2400* kp, bios_can_msg_typ* m){
    btn_set_status(&kp->btn[0], m->data[0] & 0x01);
    btn_set_status(&kp->btn[1], m->data[0] & 0x02);
    btn_set_status(&kp->btn[2], m->data[0] & 0x04);
    btn_set_status(&kp->btn[3], m->data[0] & 0x08);
    btn_set_status(&kp->btn[4], m->data[0] & 0x10);
    btn_set_status(&kp->btn[5], m->data[0] & 0x20);
    btn_set_status(&kp->btn[6], m->data[0] & 0x40);
    btn_set_status(&kp->btn[7], m->data[0] & 0x80);
}
```
{% endraw %}
<div class="caption">
    An elementary example of reading CAN traffic from a <code>.C</code> file 
</div>

{% raw %}
```c
void handle_controller_outputs(void){
    uint8_t b0 = 0;

    // Controller 01
    os_digout(DO_PWM0, pto_01);
    os_digout(DO_PWM1, blw_vac);
    os_digout(DO_PWM2, blw_psi);
    os_digout(DO_PWM3, valve_01_open);
    os_digout(DO_PWM4, reel_left);
    os_digout(DO_PWM5, reel_right);
    os_digout(DO_OUT0, accel);
    os_digout(DO_OUT1, decel);

    // Toggle & pack bits for network debugging & telematics
    b0 = b0 & ~(0x01 << 0) | (pto_01        << 0);
    b0 = b0 & ~(0x01 << 1) | (blw_vac       << 1);
    b0 = b0 & ~(0x01 << 2) | (blw_psi       << 2);
    b0 = b0 & ~(0x01 << 3) | (valve_01_open << 3);
    b0 = b0 & ~(0x01 << 4) | (reel_left     << 4);
    b0 = b0 & ~(0x01 << 5) | (reel_right    << 5);
    b0 = b0 & ~(0x01 << 6) | (accel         << 6);
    b0 = b0 & ~(0x01 << 7) | (decel         << 7);

    // Send message via proprietary CANopen
    (void)os_can_send_message(0x604, 0, 8,
        b0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);

    // Controller 02
    // Toggle & pack bits for network debugging & telematics
    b0 = b0 & ~(0x01 << 0) | (hose_in           << 0);
    b0 = b0 & ~(0x01 << 1) | (hose_out          << 1);
    b0 = b0 & ~(0x01 << 2) | (spare_01_mom      << 2);
    b0 = b0 & ~(0x01 << 3) | (spare_02_mom      << 3);
    b0 = b0 & ~(0x01 << 4) | (spare_03_latch    << 4);
    b0 = b0 & ~(0x01 << 5) | (spare_04_latch    << 5);
    b0 = b0 & ~(0x01 << 6) | (valve_02_open     << 6);

    // Send message via proprietary CANopen
    (void)os_can_send_message(0x605, 0, 8,
        b0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
}
```
{% endraw %}
<div class="caption">
    An elementary example of setting output pins in a piece of embedded software 
</div>

***

### Showcase: Developing a Project in C++ (Qt Framework)

Here is another example of the development of core system components. This excerpt is from a piece of software that I wrote to track engine maintenance reminders.

This project used <code>C++</code> and <code>Qt Framework</code> to satisfy customer demands.

{% raw %}
```c++
//------------------------------------------------------------------------------
/// \file     engine_maintenance.h
/// \brief    QObject to hold information pertaining to engine maintenance
/// \author   Saffi Kelley Kieffer, Senior Software Engineer, OPS Controls
/// \date     dd.mm.yyyy
/// \version  VV.0X.0Y.0Z
/// \module   [PRODUCT NAME]
/// \project  [CENSORED]-[CENSORED]
//------------------------------------------------------------------------------
#ifndef ENGINE_MAINTENANCE_H
#define ENGINE_MAINTENANCE_H

#include <QDebug>
#include <QFileInfo>
#include <QObject>
#include <QSettings>
#include <QTimer>
#include <cmath>
#include <unistd.h>

// Defines to remove magic numbers
#define TEST_TIME      500
#define SIX_MINS_IN_MS 360000
#define MS_IN_HR       3600000

// Define variables as Q_PROPERTY to access variables within .QML framework
class engine_maintenance : public QObject{
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
    // Constructor
    engine_maintenance();
    ~engine_maintenance();

    // Public getter functions
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

    // Helper functions
    void set_is_eng_kill(const bool &v);
    bool needs_maintenance();

    QTimer *engine_hrs_timer;

    public slots:
    // Slots for function interrupts within Qt framework
    void handle_eng_hrs_timer(bool is_low_oil_pressure);
    void reset_flags();

    private:
    // Private setter functions
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

    // Location of settings file saved within embedded system
    const QString SETTINGS_INI_FILE = "/opt/settings.ini";

    // Test Code
    // const int TIME_FOR_TIMER_Q  = TEST_TIME;

    // Production Code
    const int TIME_FOR_TIMER_Q  = SIX_MINS_IN_MS;

    // Private attributes
    float _eng_hrs;         // Engine hours, total reported
    float _eng_hrs_left;    // Engine hours, left within current maintenance period
    float _eng_hrs_this;    // Engine hours, since last maintenance recorded
    int   _maint_missed;    // Number of maintenance sessions missed
    bool  _eng_oil;         // Engine oil service needed
    bool  _eng_oil_fil;     // Engine oil filter service needed
    bool  _eng_fuel_fil;    // Engine fuel filter service needed
    bool  _pump_oil;        // Pump oil service needed
    bool  _seal_change;     // Pump seal service needed
    bool  _valve_change;    // Engine oil valve service needed
    bool  _is_eng_kill;     // Flag set by telematics to inhibit engine start

    private slots:
    // Slots for function interrupts within Qt framework
    void load_variables_from_disk();
    void save_variables_to_disk();
    void increase_eng_hrs();

    signals:
    // Function interrupts within Qt framework
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
```
{% endraw %}
<div class="caption">
    An example of an increased level of complexity from a software <code>.h</code> file 
</div>

{% raw %}
```c++
//------------------------------------------------------------------------------
/// \file     engine_maintenance.cpp
/// \brief    QObject to hold information pertaining to engine maintenance
/// \author   Saffi Kelley Kieffer, Senior Software Engineer, OPS Controls
/// \date     dd.mm.yyyy
/// \version  VV.0X.0Y.0Z
/// \module   [PRODUCT NAME]
/// \project  [CENSORED]-[CENSORED]
//------------------------------------------------------------------------------
#include "engine_maintenance.h"

// Constructor
engine_maintenance::engine_maintenance()
{
    // Start a new QTimer to record engine hours
    engine_hrs_timer = new QTimer(this);

    // Connect system interrupts with respective slots
    QObject::connect(engine_hrs_timer, SIGNAL(timeout()), this, SLOT(increase_eng_hrs()));
    QObject::connect(this, SIGNAL(is_eng_kill_changed()), this, SLOT(save_variables_to_disk()));

    // Initialize variables
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

    // Load any saved data on embedded device
    load_variables_from_disk();

    // Disable engine hours timer while engine oil is not pressurized
    handle_eng_hrs_timer(false);
}
// Destructor
engine_maintenance::~engine_maintenance()
{
    // Deallocate QTimer from heap
    delete engine_hrs_timer;
}

// Public getter functions
float engine_maintenance::eng_hrs() const       { return _eng_hrs; }
float engine_maintenance::eng_hrs_left() const  { return _eng_hrs_left; }
float engine_maintenance::eng_hrs_this() const  { return _eng_hrs_this; }
int   engine_maintenance::maint_missed() const  { return _maint_missed; }
bool  engine_maintenance::eng_oil() const       { return _eng_oil; }
bool  engine_maintenance::eng_oil_fil() const   { return _eng_oil_fil; }
bool  engine_maintenance::eng_fuel_fil() const  { return _eng_fuel_fil; }
bool  engine_maintenance::pump_oil() const      { return _pump_oil; }
bool  engine_maintenance::seal_change() const   { return _seal_change; }
bool  engine_maintenance::valve_change() const  { return _valve_change; }
bool  engine_maintenance::is_eng_kill() const   { return _is_eng_kill; }

// Private setter functions
void  engine_maintenance::set_eng_hrs(const float &v){
    if (v != _eng_hrs){
        _eng_hrs = v;
        emit eng_hrs_changed();
    }
}
void  engine_maintenance::set_eng_hrs_left(const float &v){
    if (v != _eng_hrs_left){
        _eng_hrs_left = v;
        emit eng_hrs_left_changed();
    }
}
void  engine_maintenance::set_eng_hrs_this(const float &v){
    if (v != _eng_hrs_this){
        _eng_hrs_this = v;
        emit eng_hrs_this_changed();
    }
}
void  engine_maintenance::set_maint_missed(const int &v){
    if (v != _maint_missed){
        _maint_missed = v;
        emit maint_missed_changed();
    }
}
void  engine_maintenance::set_eng_oil(const bool &v){
    if (v != _eng_oil){
        _eng_oil = v;
        emit eng_oil_changed();
    }
}
void  engine_maintenance::set_eng_oil_fil(const bool &v){
    if (v != _eng_oil_fil){
        _eng_oil_fil = v;
        emit eng_oil_fil_changed();
    }
}
void  engine_maintenance::set_eng_fuel_fil(const bool &v){
    if (v != _eng_fuel_fil){
        _eng_fuel_fil = v;
        emit eng_fuel_fil_changed();
    }
}
void  engine_maintenance::set_pump_oil(const bool &v){
    if (v != _pump_oil){
        _pump_oil = v;
        emit pump_oil_changed();
    }
}
void  engine_maintenance::set_seal_change(const bool &v){
    if (v != _seal_change){
        _seal_change = v;
        emit seal_change_changed();
    }
}
void  engine_maintenance::set_valve_change(const bool &v){
    if (v != _valve_change){
        _valve_change = v;
        emit valve_change_changed();
    }
}
void  engine_maintenance::set_is_eng_kill(const bool &v){
    if (v != _is_eng_kill){
        _is_eng_kill = v;
        emit is_eng_kill_changed();
    }
}

// Update flag if system needs maintenance on respective slots
bool  engine_maintenance::needs_maintenance(){
    return eng_oil()  || eng_oil_fil() || eng_fuel_fil() ||
           pump_oil() || seal_change() || valve_change();
}
// Ensure that timer is only running if we have oil pressure
void  engine_maintenance::handle_eng_hrs_timer(bool is_low_oil_pressure){
    if (is_low_oil_pressure){
        engine_hrs_timer->stop();
    }
    else{
        engine_hrs_timer->start(TIME_FOR_TIMER_Q);
    }
}
// Reset all flags during the case that the system has been maintained
void  engine_maintenance::reset_flags(){
    set_eng_oil     (false);
    set_eng_oil_fil (false);
    set_eng_fuel_fil(false);
    set_pump_oil    (false);
    set_seal_change (false);
    set_valve_change(false);

    set_maint_missed(0);
}
// Simple functionality to load information from memory
void  engine_maintenance::load_variables_from_disk(){
    QFileInfo file_to_check(SETTINGS_INI_FILE);

    if (file_to_check.exists() && file_to_check.isFile()){
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
// Simple functionality to save information from memory
void  engine_maintenance::save_variables_to_disk(){
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
    sync(); // Immediately write cached writes to disk
}
// Increases engine hours, called every 6 minutes (1/10th of an hour)
void  engine_maintenance::increase_eng_hrs()
{
    // Test Code
    // set_eng_hrs(eng_hrs() + 5);

    // Production Code
    set_eng_hrs(eng_hrs() + ((float)TIME_FOR_TIMER_Q/MS_IN_HR));

    // Lapsed engine hours has passed the first maintenance period
    if (eng_hrs() >= 525.0){
        // Every 500 hours set basic maintenance reminders
        if (fmod((eng_hrs() - 25), 500.0) == 0){
            set_maint_missed(maint_missed() + 1);

            set_eng_oil     (true);
            set_eng_oil_fil (true);
            set_eng_fuel_fil(true);
            set_pump_oil    (true);
        }

        // Every 3000 hours set seal maintenance reminder 
        if (fmod((eng_hrs() - 25), 3000.0) == 0){
            set_seal_change(true);
        }
        // Every 1500 hours set valve maintenance reminder
        else if (fmod((eng_hrs() - 25), 1500.0) == 0){
            set_valve_change(true);
        }

        // Set the number of hours left on the current maintenance period
        set_eng_hrs_left(500.0 - fmod((eng_hrs() - 25), 500.0));

        // Set the number of hours lapsed since the last maintenance period
        set_eng_hrs_this(-1 * ((500.0 - eng_hrs_left()) + ((maint_missed() - 1) * 500)));
    }
    else{
        set_eng_hrs_left(525.0 - eng_hrs());
        set_eng_hrs_this(eng_hrs_left());
    }

    save_variables_to_disk();
}
```
{% endraw %}
<div class="caption">
    An example of an increased level of complexity from a software <code>.CPP</code> file 
</div>

*** 

### Showcase: Testing, Verification, & Maintenance

After developing a software application system, the product goes under verification using several testing measures to ensure that it passes all unit, end-to-end, and integration testing procedures.

Following all testing procedures passing, an official manual describing product functionality is written and sent to the customer for approval.

After customer approval, the appropriate production files become populated in the internal production framework for continued sale and support.

<div class="row">
    <div class="col-sm mt-3 mt-md-0">
        {% include figure.html path="assets/img/projects/work_03/Acrobat_2023-02-07_12-34-28.png" title="Final Documentation" class="img-fluid rounded z-depth-1" %}
    </div>
</div>
<div class="caption">
    A documented excerpt of a system manual I developed outlying information for key stakeholders
</div>