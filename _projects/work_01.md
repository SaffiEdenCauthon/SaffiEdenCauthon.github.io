---
layout: page
title: Aviation Refueler
description: Showcase for industrial controls
img: assets/img/projects/work_01/blurred_img.png
importance: 1
category: work
---

### Description

During 2021-2023 I led a collaborative project with industry-leading OEM engineering departments, such as Cummins Inc, to produce a solution capable of controlling an aviation fueler. I was solely responsible for integrating full-stack solutions and technologies for this project that pertained to system logic controller hardware. This includes, but is not limited to, network architecture, UX/UI design, system programming, and the creation of several hundred pages of documentation.

This project uses a twelve-inch touch-screen display, two programmable logic controllers, and several small pieces of HMI to interface with the vehicle’s engine. The solution housed several hundred connections to outside inputs and outputs for logical processing and was able to control the refueler chassis.

<div class="row">
    <div class="col-sm mt-3 mt-md-0">
        {% include figure.html path="assets/img/projects/work_01/main_screen.png" title="The home page of the primary display." class="img-fluid rounded z-depth-1" %}
    </div>
</div>
<div class="caption">
    A screenshot of the home visualization for the aviation refueler.
</div>

<div class="row">
    <div class="col-sm mt-3 mt-md-0">
        {% include figure.html path="assets/img/projects/work_01/menu_screen_01.png" title="The menu visualization of the primary display." class="img-fluid rounded z-depth-1" %}
    </div>
</div>
<div class="caption">
    A screenshot of the menu visualization for the aviation refueler.
</div>

To integrate wire harnessing requirements, our team was able to make use of [SAE J1939](https://en.wikipedia.org/wiki/SAE_J1939) to facilitate communication on two separate networks with limited use of physical connections. One network for our solution's proprietary hardware and another to directly interface with Cummins Engine ECUs (Electronic Control Units).

Using these networks, I developed several utilities that became company-standard across strategic partner groups. One such utility was methods that encoded and decoded packet data sent across the J1939 networks. This method allowed the successful decoding of data as defined in the J1939 standard.

For more information regarding the complex nature of J1939 communication, feel free to read [this documentation](https://www.csselectronics.com/pages/j1939-explained-simple-intro-tutorial) or send me a message.

<div class="row justify-content-sm-center">
    <div class="col-sm-6 mt-3 mt-md-0">
        {% include figure.html path="assets/img/projects/work_01/PcanSEdt_2023-02-07_12-13-00.png" title="example image" class="img-fluid rounded z-depth-1" %}
    </div>
    <div class="col-sm-6 mt-3 mt-md-0">
        {% include figure.html path="assets/img/projects/work_01/CODESYS_2023-02-07_12-10-15.png" title="example image" class="img-fluid rounded z-depth-1" %}
    </div>
</div>
<div class="caption">
    An example showing the high-level structure of a PGN (data packet), and the software to decode the array of data.
</div>

Other notable examples of expertise in this project come from the software written to interface with active diagnostic troubleshooting codes on a J1939 engine chassis. 

In the code excerpt below, we implement functionality to decode [SAE J1939’s transport protocol](https://www.csselectronics.com/pages/j1939-explained-simple-intro-tutorial#j1939-transport-protocol).

In turn, this will allow us to know if there is a check engine light on the vehicle and why it is appearing.

{% raw %}
```c++
// Transport Protocol - Connection Management
case TPCM_BAM: {
    // Reset the buffer after declaration of new multi-packet broadcast
    for (int i = 0; i < TPDT_BUFFER_SIZE; ++i) {
        TPDT_Buffer[i] = 0x00;
    }

    // Set SPN 2567-2569 within engine data structure
    // This will be used when we receive the TPDT SPN message
    // To set information pertaining to engine diagnostic codes
    TPCM_BAM_TotalMessageSize        = decode(msg->data,  8, 16, false, false, 1, 0);
    TPCM_BAM_TotalNumberOfPackets    = decode(msg->data, 24,  8, false, false, 1, 0);
    TPCM_BAM_PGNOfThePacketedMessage = decode(msg->data, 40, 24, false, false, 1, 0);
    break;
}

// Transport Protocol - Data Transfer
case TPDT: {
    // Get SPN 2572, the current sequence number in the multi-packet broadcast
    float TPDT_SequenceNumber = decode(msg->data, 0, 8, false, false, 1, 0);

    // Convert into a useable metric for the loop below
    int seq_num = static_cast<int>(TPDT_SequenceNumber) - 1;

    // Place the remaining 7 bytes of data within a buffer of many bytes
    for (int i = 1; i < 8; ++i){
        int buffer_index = (i - 1) + (seq_num * 7);
        TPDT_Buffer[buffer_index] = msg->data[i];
    }

    // The sequence reported is the last of the multi-packet transport
    if (TPDT_SequenceNumber == TPCM_BAM_TotalNumberOfPackets){
        // Check which PGN was being broadcast
        switch (static_cast<int>(TPCM_BAM_PGNOfThePacketedMessage)){
            // Broadcasted buffer contains data pertaining to active DTCs
            case 0xFECA: {
                // First two bytes of data are engine lamp status
                // After, four bytes of data are sent for every DTC on the chassis
                int number_of_dtcs = ((TPCM_BAM_TotalMessageSize) - 2) / 4;

                // Create struct to hold the active diagnostic messages
                DiagMsg temp[number_of_dtcs];

                // Decode active engine lamp status
                eng->setDM01_ProtectLamp                  (decode(TPDT_Buffer,  0, 2, false, false, 1, 0));
                eng->setDM01_AmberWarningLamp             (decode(TPDT_Buffer,  2, 2, false, false, 1, 0));
                eng->setDM01_RedStopLamp                  (decode(TPDT_Buffer,  4, 2, false, false, 1, 0));
                eng->setDM01_MalfunctionIndicatorLamp     (decode(TPDT_Buffer,  6, 2, false, false, 1, 0));
                eng->setDM01_FlashProtectLamp             (decode(TPDT_Buffer,  8, 2, false, false, 1, 0));
                eng->setDM01_FlashAmberWarningLamp        (decode(TPDT_Buffer, 10, 2, false, false, 1, 0));
                eng->setDM01_FlashRedStopLamp             (decode(TPDT_Buffer, 12, 2, false, false, 1, 0));
                eng->setDM01_FlashMalfunctionIndicatorLamp(decode(TPDT_Buffer, 14, 2, false, false, 1, 0));

                // Determine which lamp to display on gauge_screen.qml (visualization)
                handleHighestLamp();

                // Fill in precise information from DTC libraries
                for (int i = 0; i < number_of_dtcs; ++i){
                    
                    // Get unique identifier of suspect parameter numbers & failure mode identifier
                    temp[i].spnCode = static_cast<u_int32_t>(decode(TPDT_Buffer, 23, 19, false, false, 1, 0));
                    temp[i].fmiCode = static_cast<u_int8_t> (decode(TPDT_Buffer, 32,  5, false, false, 1, 0));

                    // Get the unique description using the unique identifiers
                    temp[i].spnDescription = getSpnDesc(temp[i].spnCode);
                    temp[i].fmiDescription = getFmiDesc(temp[i].fmiCode);

                    // Get the engine lamp status, set by the particular DTC
                    temp[i].lamp = getDtcFaultLamp(temp[i].fmiCode, temp[i].spnCode);

                    // Get the unique description for JohnDeere Products
                    temp[i].johnDeereDescription = getJdDesc(temp[i].fmiCode, temp[i].spnCode);

                    // Add the faults to the buffer of active diagnostic troubleshooting codes
                    if (temp[i].spnCode != 0 || temp[i].fmiCode != 0){
                        currentFaults->insertFault(temp[i]);
                    }
                }
                break;
            }
        }
    }
    break;
}
```
{% endraw %}
