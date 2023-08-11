/**
 * @file test_ty.cc
 * @author your name (you@domain.com)
 * @brief 图漾深度相机的单元测试
 * @version 0.1
 * @date 2023-08-11
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#include "TYApi.h"
#include "TyIsp.h"

#include "TYThread.hpp"
#include "BayerISP.hpp"
#include "MatViewer.hpp"
#include "common.hpp"

int test_opencv()
{
    cv::Mat depth;

    depth = cv::imread("path/to/aaa-frame-6123.jpg");

    cv::imshow("test ty", depth);

    cv::waitKey(0);

    return 0;
}

void PrintTYVersion(TY_VERSION_INFO *ver)
{
    std::cerr << "major: " << ver->major << "\n"
              << "minor: " << ver->minor << "\n"
              << "patch: " << ver->patch << "\n"
              << "reserved: " << ver->reserved << "\n"
              << std::endl;
}

void eventCallback(TY_EVENT_INFO *event_info, void *userdata)
{
    if (event_info->eventId == TY_EVENT_DEVICE_OFFLINE) {
        std::cerr << "=== Event Callback: Device Offline!" << std::endl;
        // Note:
        //     Please set TY_BOOL_KEEP_ALIVE_ONOFF feature to false if you need to debug with breakpoint!
    }
    else if (event_info->eventId == TY_EVENT_LICENSE_ERROR) {
        std::cerr << "=== Event Callback: License Error!" << std::endl;
    }
}

// static int get_fps() {
//     static int fps_counter = 0;
//     static clock_t fps_tm = 0;
//     const int kMaxCounter = 200;
//     struct timeval start;
//     fps_counter++;
//     if (fps_counter < kMaxCounter) {
//         return -1;
//     }

//     gettimeofday(&start, NULL);
//     int elapse = start.tv_sec * 1000 + start.tv_usec / 1000 - fps_tm;
//     int v = (int)(((float)fps_counter) / elapse * 1000);
//     gettimeofday(&start, NULL);
//     fps_tm = start.tv_sec * 1000 + start.tv_usec / 1000;

//     fps_counter = 0;
//     return v;
// }

int main()
{
    int ret;
    TY_VERSION_INFO ver;

    ret = TYInitLib();
    if (ret != TY_STATUS_OK)
    {
        std::cerr << "failed to init TY library" << std::endl;
        return -1;
    }
    ret = TYLibVersion(&ver);
    if (ret != TY_STATUS_OK)
    {
        std::cerr << "failed to get TY version info" << std::endl;
        return -1;
    }
    PrintTYVersion(&ver);

    ret = TYUpdateInterfaceList();
    if (ret != TY_STATUS_OK)
    {
        std::cerr << "failed to update current interfaces" << std::endl;
        return -1;
    }

    uint32_t interface_num = 0;
    ret = TYGetInterfaceNumber(&interface_num);
    if (ret != TY_STATUS_OK)
    {
        std::cerr << "failed to get interfaces number" << std::endl;
        return -1;
    }
    std::cerr << "Got " << interface_num << " interface list" << std::endl;
    if (interface_num == 0)
    {
        std::cerr << "interface number incorrect" << std::endl;
        return -1;
    }

    std::vector<TY_INTERFACE_INFO> interface_arr(interface_num);
    ret = TYGetInterfaceList(&interface_arr[0], interface_num, &interface_num);
    if (ret != TY_STATUS_OK)
    {
        std::cerr << "failed to get interfaces list info" << std::endl;
        return -1;
    }
    if (interface_num != interface_arr.size())
    {
        std::cerr << "the fill num no equal array's size" << std::endl;
        return -1;
    }
    for (uint32_t col{0}; col < interface_num; col++)
    {
        std::cerr << "Found interface : " << col << "\n"
                  << "name : " << interface_arr[col].name << "\n"
                  << "id : " << interface_arr[col].id << "\n"
                  << "type: " << interface_arr[col].type << "\n"
                  << std::endl;
        if (TYIsNetworkInterface(interface_arr[col].type))
        {
            std::cerr << "MAC: " << interface_arr[col].netInfo.mac << "\n"
                      << "ip: " << interface_arr[col].netInfo.ip << "\n"
                      << "netmask: " << interface_arr[col].netInfo.netmask << "\n"
                      << "gateway: " << interface_arr[col].netInfo.gateway << "\n"
                      << "broadcast: " << interface_arr[col].netInfo.broadcast << "\n"
                      << std::endl;
        }
    }

    std::string ID{};
    std::string IP{};
    uint32_t device_num{1};
    TY_INTERFACE_TYPE iface{TY_INTERFACE_ALL};
    std::vector<TY_DEVICE_BASE_INFO> out;
    std::vector<TY_INTERFACE_TYPE> interface_type_list;
    std::vector<TY_INTERFACE_HANDLE> interface_handle_arr;

    interface_type_list.push_back(TY_INTERFACE_USB);
    interface_type_list.push_back(TY_INTERFACE_ETHERNET);
    interface_type_list.push_back(TY_INTERFACE_IEEE80211);
    for (size_t col{0}; col < interface_type_list.size(); col++)
    {
        for (uint32_t row{0}; row < interface_arr.size(); row++)
        {
            if (interface_arr[row].type == interface_type_list[col] &&
                (interface_arr[row].type & iface) &&
                device_num > out.size())
            {
                TY_INTERFACE_HANDLE interface_handle;
                ret = TYOpenInterface(interface_arr[row].id, &interface_handle);
                if (ret != TY_STATUS_OK)
                {
                    std::cerr << "failed to open interface" << std::endl;
                    continue;
                }
                interface_handle_arr.push_back(interface_handle);
            }
        }
    }
    updateDevicesParallel(interface_handle_arr);
    for (uint32_t col {0}; col < interface_handle_arr.size(); col++)
    {
        uint32_t n = 0;
        TY_INTERFACE_HANDLE interface_handle = interface_handle_arr[col];
        TYGetDeviceNumber(interface_handle, &n);
        if (n <= 0)
        {
            TYCloseInterface(interface_handle);
            continue;
        }
        std::vector<TY_DEVICE_BASE_INFO> device_arr(n);
        TYGetDeviceList(interface_handle, &device_arr[0], n, &n);
        for (uint32_t row{0}; row < n; row++)
        {
            if (device_num > out.size() &&
                ((ID.empty() && IP.empty()) ||
                (!ID.empty() && device_arr[row].id == ID) ||
                (!IP.empty() && IP == device_arr[row].netInfo.ip))
                )
            {
                if (device_arr[row].iface.type == TY_INTERFACE_ETHERNET ||
                    device_arr[row].iface.type == TY_INTERFACE_IEEE80211)
                {
                    std::cerr << "Select " << device_arr[row].id << " on " << device_arr[row].iface.id
                              << ", ip : " << device_arr[row].netInfo.ip << "\n"
                              << std::endl;
                }
                else
                {
                    std::cerr << "Select " << device_arr[row].id << " on " << device_arr[row].iface.id << "\n"
                              << std::endl;
                }
                out.push_back(device_arr[row]);
            }
        }
        TYCloseInterface(interface_handle);
    }
    if (out.size() == 0)
    {
        std::cerr << "not found any device" << std::endl;
        return -1;
    }

    TY_INTERFACE_HANDLE interface_handle = NULL;
    TY_DEV_HANDLE device_handle = NULL;
    TY_DEVICE_BASE_INFO& selected_device = out[0];
    ret = TYOpenInterface(selected_device.iface.id, &interface_handle);
    if (ret != TY_STATUS_OK)
    {
        std::cerr << "failed to open interface" << std::endl;
        return -1;
    }
    ret = TYOpenDevice(interface_handle, selected_device.id, &device_handle);
    if (ret != TY_STATUS_OK)
    {
        std::cerr << "failed to open device" << std::endl;
        return -1;
    }

    TY_COMPONENT_ID allComps;
    ret = TYGetComponentIDs(device_handle, &allComps);
    if (ret != TY_STATUS_OK)
    {
        std::cerr << "failed to get all component ids" << std::endl;
        return -1;
    }

    int32_t color = 1;
    int32_t ir = 1;
    TY_ISP_HANDLE color_isp_handle = NULL;
    if (allComps & TY_COMPONENT_RGB_CAM && color)
    {
        ret = TYEnableComponents(device_handle, TY_COMPONENT_RGB_CAM);
        if (ret != TY_STATUS_OK)
        {
            std::cerr << "failed to enable rgb camera" << std::endl;
            return -1;
        }
        ret = TYISPCreate(&color_isp_handle);
        if (ret != TY_STATUS_OK)
        {
            std::cerr << "failed to create isp handle" << std::endl;
            return -1;
        }
        ret = ColorIspInitSetting(color_isp_handle, device_handle);
        if (ret != TY_STATUS_OK)
        {
            std::cerr << "failed to init isp setting" << std::endl;
            return -1;
        }
        ColorIspShowSupportedFeatures(color_isp_handle);
    #ifdef OPEN_AUTO_EXPOSURE_FUNCTION
        ret = ColorIspInitAutoExposure(color_isp_handle, device_handle);
        if (ret != TY_STATUS_OK)
        {
            std::cerr << "failed to open auto exposure function in isp" << std::endl;
            return -1;
        }
    #endif
    }

    if (allComps & TY_COMPONENT_IR_CAM_LEFT && ir)
    {
        std::cerr << "has IR left camera, open IR left cam" << std::endl;
        ret = TYEnableComponents(device_handle, TY_COMPONENT_IR_CAM_LEFT);
        if (ret != TY_STATUS_OK)
        {
            std::cerr << "failed to open IR lef setting" << std::endl;
            return -1;
        }
    }
    if (allComps & TY_COMPONENT_IR_CAM_RIGHT && ir)
    {
        std::cerr << "has IR right camera, open IR right cam" << std::endl;
        ret = TYEnableComponents(device_handle, TY_COMPONENT_IR_CAM_RIGHT);
        if (ret != TY_STATUS_OK)
        {
            std::cerr << "failed to open IR right setting" << std::endl;
            return -1;
        }
    }

    std::cerr << "Configure components, open depth cam" << std::endl;
    /**
     * @brief class DepthViewer --> MatViewer.hpp --> DepthRender.hpp
     *
     */
    int32_t depth = 1;
    DepthViewer depth_viewer("Depth");
    if (allComps & TY_COMPONENT_DEPTH_CAM && depth)
    {
        TY_IMAGE_MODE image_mode;
        ret = get_default_image_mode(device_handle, TY_COMPONENT_DEPTH_CAM, image_mode);
        if (ret != TY_STATUS_OK)
        {
            std::cerr << "failed to get default image mode" << std::endl;
            return -1;
        }
        std::cerr << "Select Depth Image Mode: " << TYImageWidth(image_mode)
                  << " x " << TYImageHeight(image_mode) << "\n"
                  << std::endl;
        ret = TYSetEnum(device_handle, TY_COMPONENT_DEPTH_CAM, TY_ENUM_IMAGE_MODE, image_mode);
        if (ret != TY_STATUS_OK)
        {
            std::cerr << "failed to set enum" << std::endl;
            return -1;
        }
        ret = TYEnableComponents(device_handle, TY_COMPONENT_DEPTH_CAM);
        if (ret != TY_STATUS_OK)
        {
            std::cerr << "failed to enable depth component" << std::endl;
            return -1;
        }
        //depth map pixel format is uint16_t ,which default unit is  1 mm
        //the acutal depth (mm)= PixelValue * ScaleUnit
        float scale_unit = 1.;
        TYGetFloat(device_handle, TY_COMPONENT_DEPTH_CAM, TY_FLOAT_SCALE_UNIT, &scale_unit);
        depth_viewer.depth_scale_unit = scale_unit;
    }

    std::cerr << "prepare image buffer" << std::endl;
    uint32_t frame_size;
    ret = TYGetFrameBufferSize(device_handle, &frame_size);
    if (ret != TY_STATUS_OK)
    {
        std::cerr << "failed to get frame buffer size" << std::endl;
        return -1;
    }
    std::cerr << "Get size of framebuffer, " << frame_size << std::endl;

    std::cerr << "Allocate & enqueue buffers" << std::endl;
    char* frame_buffer[2];
    frame_buffer[0] = new char[frame_size];
    frame_buffer[1] = new char[frame_size];
    std::cerr << "Enqueue buffer (" << &frame_buffer[0] << ", " << frame_size << ") \n" << std::endl;
    ret = TYEnqueueBuffer(device_handle, frame_buffer[0], frame_size);
    if (ret != TY_STATUS_OK)
    {
        std::cerr << "failed to enqueue frame from device" << std::endl;
        return -1;
    }
    std::cerr << "Enqueue buffer (" << &frame_buffer[1] << ", " << frame_size << ") \n" << std::endl;
    ret = TYEnqueueBuffer(device_handle, frame_buffer[1], frame_size);
    if (ret != TY_STATUS_OK)
    {
        std::cerr << "failed to enqueue frame from device" << std::endl;
        return -1;
    }

    std::cerr << "Register event callback" << std::endl;
    ret = TYRegisterEventCallback(device_handle, eventCallback, NULL);
    if (ret != TY_STATUS_OK)
    {
        std::cerr << "failed to register eventCallback" << std::endl;
        return -1;
    }

    bool hasTrigger;
    ret = TYHasFeature(device_handle, TY_COMPONENT_DEVICE, TY_STRUCT_TRIGGER_PARAM, &hasTrigger);
    if (ret != TY_STATUS_OK)
    {
        std::cerr << "failed to get trigger feature status" << std::endl;
        return -1;
    }
    if (hasTrigger)
    {
        std::cerr << "Disable trigger mode" << std::endl;
        TY_TRIGGER_PARAM trigger;
        trigger.mode = TY_TRIGGER_MODE_OFF;
        ret = TYSetStruct(device_handle, TY_COMPONENT_DEVICE, TY_STRUCT_TRIGGER_PARAM, &trigger, sizeof(trigger));
        if (ret != TY_STATUS_OK)
        {
            std::cerr << "failed to set trigger feature configuration" << std::endl;
            return -1;
        }
    }

    std::cerr << "Start capture" << std::endl;
    ret = TYStartCapture(device_handle);
    if (ret != TY_STATUS_OK)
    {
        std::cerr << "failed to start capture from device" << std::endl;
        return -1;
    }

    std::cerr << "while loop to fetch frame" << std::endl;
    bool exit_main = false;
    TY_FRAME_DATA frame;
    int index = 0;
    while (!exit_main)
    {
        int err = TYFetchFrame(device_handle, &frame, -1);
        if (err != TY_STATUS_OK)
            continue;

        std::cerr << "Get frame " << ++index << std::endl;
        int fps = get_fps();
        if (fps > 0)
        {
            std::cerr << "fps: " << fps << std::endl;
        }

        cv::Mat depth, irl, irr, color;
        parseFrame(frame, &depth, &irl, &irr, &color, color_isp_handle);
        if (!depth.empty())
        {
            depth_viewer.show(depth);
        }
        if (!irl.empty())
        {
            cv::imshow("LeftIR", irl);
        }
        if (!irr.empty())
        {
            cv::imshow("RightIR", irr);
        }
        if (!color.empty())
        {
            cv::imshow("Color", color);
        }

        int key = cv::waitKey(1);
        switch (key & 0xff)
        {
        case 0xff:
            break;
        case 'q':
            exit_main = true;
            break;
        default:
            std::cerr << "Unmapped key: " << key << std::endl;
        }

        TYISPUpdateDevice(color_isp_handle);
        std::cerr << "Re-enqueue buffer (" << frame.userBuffer << ", " << frame.bufferSize << std::endl;
        ret = TYEnqueueBuffer(device_handle, frame.userBuffer, frame.bufferSize);
        if (ret != TY_STATUS_OK)
        {
            std::cerr << "failed to enqueue frame to buffer" << std::endl;
            break;
        }
    }

    ret = TYStopCapture(device_handle);
    if (ret != TY_STATUS_OK)
    {
        std::cerr << "failed to stop capture from device" << std::endl;
        return -1;
    }
    ret = TYCloseDevice(device_handle);
    if (ret != TY_STATUS_OK)
    {
        std::cerr << "failed to close device" << std::endl;
        return -1;
    }
    ret = TYCloseInterface(interface_handle);
    if (ret != TY_STATUS_OK)
    {
        std::cerr << "failed to close interface" << std::endl;
        return -1;
    }
    ret = TYISPRelease(&color_isp_handle);
    if (ret != TY_STATUS_OK)
    {
        std::cerr << "failed to close isp" << std::endl;
        return -1;
    }
    ret = TYDeinitLib();
    if (ret != TY_STATUS_OK)
    {
        std::cerr << "failed to deinit library" << std::endl;
        return -1;
    }
    delete frame_buffer[0];
    delete frame_buffer[1];

    std::cerr << "---main done---" << std::endl;
    return 0;
}