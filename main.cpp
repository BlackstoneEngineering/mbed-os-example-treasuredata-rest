/* WiFi Example
 * Copyright (c) 2016 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mbed.h"
#include "treasure-data-rest.h"

#define BUFF_SIZE   100

// Default network interface object. Don't forget to change the WiFi SSID/password in mbed_app.json if you're using WiFi.
NetworkInterface *net = NetworkInterface::get_default_instance();

int main(void){

    printf("\r\nTreasure Data REST API Demo\n");

    // Connect to the internet (DHCP is expected to be on)
    printf("Connecting to the network using the default network interface...\n");
    net = NetworkInterface::get_default_instance();

    nsapi_error_t net_status = -1;
    for (int tries = 0; tries < 3; tries++) {
        net_status = net->connect();
        if (net_status == NSAPI_ERROR_OK) {
            break;
        } else {
            printf("Unable to connect to network. Retrying...\n");
        }
    }

    if (net_status != NSAPI_ERROR_OK) {
        printf("ERROR: Connecting to the network failed (%d)!\n", net_status);
        return -1;
    }

    printf("Connected to the network successfully. IP address: %s\n", net->get_ip_address());

    printf("Success\n\n");
    printf("MAC: %s\n", net->get_mac_address());
    printf("IP: %s\n", net->get_ip_address());
    printf("Netmask: %s\n", net->get_netmask());
    printf("Gateway: %s\n", net->get_gateway());
    // printf("RSSI: %d\n\n", net.get_rssi());

    // Create Treasure data objects (Network, Database, Table, APIKey)
    TreasureData_RESTAPI* heap  = new TreasureData_RESTAPI(net,"test_database","heap_info", MBED_CONF_APP_API_KEY);
    TreasureData_RESTAPI* cpu   = new TreasureData_RESTAPI(net,"test_database","cpu_info",  MBED_CONF_APP_API_KEY);
    TreasureData_RESTAPI* stack = new TreasureData_RESTAPI(net,"test_database","stack_info",MBED_CONF_APP_API_KEY);
    TreasureData_RESTAPI* sys   = new TreasureData_RESTAPI(net,"test_database","sys_info",  MBED_CONF_APP_API_KEY);

    // Device Information Objects
    mbed_stats_cpu_t    cpuinfo;
    mbed_stats_heap_t   heapinfo;
    mbed_stats_stack_t  stackinfo;
    mbed_stats_sys_t    sysinfo;

    // Buffers to create strings in
    char cpu_buff  [BUFF_SIZE] = {0};
    char heap_buff [BUFF_SIZE] = {0};
    char stack_buff[BUFF_SIZE] = {0};
    char sys_buff  [BUFF_SIZE] = {0};

    int x = 0;

    // Get device health data, send to Treasure Data every 10 seconds
    while(1){
        {
            // Collect local data
            mbed_stats_cpu_get(  &cpuinfo);

            // Construct strings to send
            x = sprintf(cpu_buff,"{\"uptime\":%d,\"idle_time\":%d,\"sleep_time\":%d,\"deep_sleep_time\":%d}",
                                cpuinfo.uptime,
                                cpuinfo.idle_time,
                                cpuinfo.sleep_time,
                                cpuinfo.deep_sleep_time);
            cpu_buff[x]=0; // null terminate the string

            // Send data to Treasure data
            printf("\r\n Sending CPU Data: '%s'\r\n",cpu_buff);
            cpu->sendData(cpu_buff,strlen(cpu_buff));
        }
        {
            // Collect local data
            mbed_stats_heap_get(  &heapinfo);

            // Construct strings to send
            x=sprintf(heap_buff,"{\"current_size\":%d,\"max_size\":%d,\"total_size\":%d,\"reserved_size\":%d,\"alloc_cnt\":%d,\"alloc_fail_cnt\":%d}",
                                heapinfo.current_size,
                                heapinfo.max_size,
                                heapinfo.total_size,
                                heapinfo.reserved_size,
                                heapinfo.alloc_cnt,
                                heapinfo.alloc_fail_cnt);
            heap_buff[x]=0; // null terminate the string

            // Send data to Treasure data
            printf("\r\n Sending Heap Data: '%s'\r\n",heap_buff);
            heap->sendData(heap_buff,strlen(heap_buff));
        }
        {
            // Collect local data
            mbed_stats_stack_get(  &stackinfo);

            // Construct strings to send
            x=sprintf(stack_buff,"{\"thread_id\":%d,\"max_size\":%d,\"reserved_size\":%d,\"stack_cnt\":%d}",
                                stackinfo.thread_id,
                                stackinfo.max_size,
                                stackinfo.reserved_size,
                                stackinfo.stack_cnt);
            stack_buff[x]=0; // null terminate the string

            // Send data to Treasure data
            printf("\r\n Sending Stack Data: '%s'\r\n",stack_buff);
            stack->sendData(stack_buff,strlen(stack_buff));
        }
        {
            // Collect local data
            mbed_stats_sys_get(  &sysinfo);

            // Construct strings to send
            x=sprintf(sys_buff,"{\"os_version\":%d,\"cpu_id\":%d,\"compiler_id\":%d,\"compiler_version\":%d}",
                                sysinfo.os_version,
                                sysinfo.cpu_id,
                                sysinfo.compiler_id,
                                sysinfo.compiler_version);
            sys_buff[x]=0; // null terminate the string

            // Send data to Treasure data
            printf("\r\n Sending System Data: '%s'\r\n",sys_buff);
            sys->sendData(sys_buff,strlen(sys_buff));
        }
        wait(10);

    }

    // Code should not get here, included for completeness
    net->disconnect();

    printf("\nDone, x=%d\n",x);

}
