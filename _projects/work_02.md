---
layout: page
title: Industrial Equipment
description: Showcase of Legacy Overhaul
img: assets/img/projects/work_02/blurred_img.png
importance: 2
category: work
---

### Project Description & Overview

> In 2022 I led a collaborative project with an outside OEM engineering department to completely overhaul a legacy system for a **fifty-ton remotely controlled piece of industrial equipment**.

I was solely responsible for integrating full-stack solutions and technologies for this project that pertained to system hardware. This includes, but is not limited to, network architecture, UX/UI design, system programming, and the creation of several hundred pages of documentation.

This project uses a twelve-inch touch-screen display, a programmable logic controller, and several pieces of radio equipment to interface with the vehicle’s engine. The solution housed several hundred connections to outside inputs and outputs for logical processing and controlled most aspects of the equipment. Pieces of the machinery controlled by safety-regulated functions include the rail tracks, screen, feeder, and conveyors.

<div class="row">
    <div class="col-sm mt-3 mt-md-0">
        {% include figure.html path="assets/img/projects/work_02/CODESYS_2023-02-07_11-58-00.png" title="Prototype Within Designer Framework" class="img-fluid rounded z-depth-1" %}
    </div>
</div>
<div class="caption">
    The system prototype, as viewed within the development framework
</div>

***

### Showcase: Strategic Partnerships
This project started as a simple change requested at a trade show. Initially, it included a redesign of a remote control system. The initial redesign for the remote control solution was **completed in record time and exceeded customer requirements**. Because of this, my company was able to secure a large contract to **redesign the entire industrial vehicle system**. As such, this project is one of the favorites I have ever had the pleasure of taking part in.

<div class="row">
    <div class="col-sm mt-3 mt-md-0">
        {% include figure.html path="assets/img/projects/work_02/large screen.jpg" title="Legacy System Installed On Vehicle" class="img-fluid rounded z-depth-1" %}
    </div>
</div>
<div class="caption">
    The legacy system hardware on a piece of industrial equipment
</div>

***

### Showcase: Indentifying Core System Requirements

One of my favorite pieces of software that I developed within this solution was <code>Output Status Visualization</code>. This visualization was in response to an undocumented customer desire during project planning.

In short, this visualization allows an administrative-level user to force an output’s status while the machine is in a safe state, allowing for crucial maintenance and production tasks to be expedited by an experienced operator.

Further, information about each pin is displayed in a neatly organized manner that corresponds to wiring schematics. The user can then click on each output to view any available diagnostic notifications by the system’s operating system.

<div class="row">
    <div class="col-sm mt-3 mt-md-0">
        {% include figure.html path="assets/img/projects/work_02/CODESYS_2023-02-07_11-59-08.png" title="Output Status Visualization" class="img-fluid rounded z-depth-1" %}
    </div>
</div>
<div class="caption">
    The system prototype’s <code>Output Status Visualization</code>
</div>

***

### Showcase: Upgrading Legacy Software Systems

Another improved functionality from the legacy system is the <code>Maintenance Visualization</code>. This redesigned page allows the end-user to read data, one functional piece at a time. Before this update, this page showed an Excel-like spreadsheet of over a dozen rows, one for each function that needed maintenance. 

Further improved functionality includes exporting maintenance a <code>.CSV</code> of maintenance data via USB or the cloud via an installed telematics solution.

<div class="row">
    <div class="col-sm mt-3 mt-md-0">
        {% include figure.html path="assets/img/projects/work_02/CODESYS_2023-02-07_11-59-47.png" title="The home page of the primary display." class="img-fluid rounded z-depth-1" %}
    </div>
</div>
<div class="caption">
    The system prototype’s <code>Maintenance Visualization</code>
</div>

***

### Showcase: Overcoming Hurdles

Finally, another improved piece of functionality was the creation of an accessible <code>Time_To_Epoch()</code> function. This function was developed as the vendor for the programmable logic controller did not have a front-facing way to access a date-time stamp as a UNIX time stamp.

With a few lines of code, I was able to swiftly implement a customer-level request within a few moments of research. This process was deemed system-critical to keep the backward compatibility of <code>.CSV</code> files from legacy systems.

<div class="row">
    <div class="col-sm mt-3 mt-md-0">
        {% include figure.html path="assets/img/projects/work_02/CODESYS_2023-02-07_12-03-42.png" title="Time_To_Epoch() Function" class="img-fluid rounded z-depth-1" %}
    </div>
</div>
<div class="caption">
    The function converts operating-system-defined variables into a new data type
</div>