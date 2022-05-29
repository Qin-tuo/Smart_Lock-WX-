
//��Ƭ��ͷ�ļ�
#include "stm32f10x.h"

//�����豸
#include "esp8266.h"

//Э���ļ�
#include "onenet.h"
#include "mqttkit.h"

//Ӳ������
#include "usart.h"
#include "delay.h"
#include "main.h"

// C��
#include <string.h>
#include <stdio.h>

#define PROID "508382"

#define AUTH_INFO "123456"

#define DEVID "932077948"

extern unsigned char esp8266_buf[128];
double temp, humi;
u8 key = 0;
u8 warn = 0;

//==========================================================
//	�������ƣ�	OneNet_DevLink
//
//	�������ܣ�	��onenet��������
//
//	��ڲ�����	��
//
//	���ز�����	1-�ɹ�	0-ʧ��
//
//	˵����		��onenetƽ̨��������
//==========================================================
_Bool OneNet_DevLink(void)
{

    MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 1}; //Э���

    unsigned char* dataPtr;

    _Bool status = 1;

    //	UsartPrintf(USART_DEBUG,"OneNET_DevLink\r\n");
    //	UsartPrintf(USART_DEBUG,"PROID: %s,	AUIF: %s,	DEVID:%s\r\n", PROID, AUTH_INFO, DEVID);

    if(MQTT_PacketConnect(PROID, AUTH_INFO, DEVID, 512, 0, MQTT_QOS_LEVEL0, NULL, NULL, 0, &mqttPacket) == 0)
    {
        ESP8266_SendData(mqttPacket._data, mqttPacket._len); //�ϴ�ƽ̨

        dataPtr = ESP8266_GetIPD(250); //�ȴ�ƽ̨��Ӧ
        if(dataPtr != NULL)
        {
            if(MQTT_UnPacketRecv(dataPtr) == MQTT_PKT_CONNACK)
            {
                switch(MQTT_UnPacketConnectAck(dataPtr))
                {
                case 0:
                    status = 0;
                    break; // UsartPrintf(USART_DEBUG, "Tips:	���ӳɹ�\r\n");

                case 1:
                    break; // UsartPrintf(USART_DEBUG, "WARN:	����ʧ�ܣ�Э�����\r\n");
                case 2:
                    break; // UsartPrintf(USART_DEBUG, "WARN:	����ʧ�ܣ��Ƿ���clientid\r\n");
                case 3:
                    break; // UsartPrintf(USART_DEBUG, "WARN:	����ʧ�ܣ�������ʧ��\r\n");
                case 4:
                    break; // UsartPrintf(USART_DEBUG, "WARN:	����ʧ�ܣ��û������������\r\n");
                case 5:
                    break; // UsartPrintf(USART_DEBUG, "WARN:	����ʧ�ܣ��û������������\r\n");

                default:
                    break; // UsartPrintf(USART_DEBUG, "ERR:	����ʧ�ܣ�δ֪����\r\n");
                }
            }
        }

        MQTT_DeleteBuffer(&mqttPacket); //ɾ��
        ESP8266_Clear();
    }
    //	else
    //		UsartPrintf(USART_DEBUG, "WARN:	MQTT_PacketConnect Failed\r\n");

    return status;
}

unsigned char OneNet_FillBuf(char* buf) // Type3   CJson��ʽ
{

    char text[255];

    memset(text, 0, sizeof(text));

    strcpy(buf, ",;");

    memset(text, 0, sizeof(text));
    sprintf(text, "key,%d;", key);
    strcat(buf, text);

    memset(text, 0, sizeof(text));
    sprintf(text, "warn,%d;", warn);
    strcat(buf, text);

    return strlen(buf);
}

//==========================================================
//	�������ƣ�	OneNet_SendData
//
//	�������ܣ�	�ϴ����ݵ�ƽ̨
//
//	��ڲ�����	type���������ݵĸ�ʽ
//
//	���ز�����	��
//
//	˵����
//==========================================================
char buf[255];
void OneNet_SendData(void)
{

    MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0}; //Э���

    int body_len = 0, i = 0;

    //	UsartPrintf(USART_DEBUG,"Tips:	OneNet_SendData-MQTT\r\n");

    memset(buf, 0, sizeof(buf));

    body_len = OneNet_FillBuf(buf); //��װ����ΪCJson��ʽ����ȡ���ݳ���
    //	UsartPrintf(USART_DEBUG, "%s\r\n",buf);//�����͵����ݴ�ӡ����
    if(body_len)
    {
        if(MQTT_PacketSaveData(DEVID, body_len, NULL, 5, &mqttPacket) == 0)  //���������Ϊ��ʽ3
        {
            for(; i < body_len; i++)
                mqttPacket._data[mqttPacket._len++] = buf[i];

            ESP8266_SendData(mqttPacket._data, mqttPacket._len); //�ϴ����ݵ�ƽ̨
            //			UsartPrintf(USART_DEBUG, "Send %d Bytes\r\n", mqttPacket._len);

            MQTT_DeleteBuffer(&mqttPacket); //ɾ��
        }
        //		else
        //			UsartPrintf(USART_DEBUG,"WARN:	MQTT_NewBuffer Failed\r\n");
    }
}

//==========================================================
//	�������ƣ�	OneNet_RevPro
//
//	�������ܣ�	ƽ̨�������ݼ��
//
//	��ڲ�����	dataPtr��ƽ̨���ص�����
//
//	���ز�����	��
//
//	˵����
//==========================================================
void OneNet_RevPro(unsigned char* cmd)
{

    MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0}; //Э���

    char* req_payload = NULL;
    char* cmdid_topic = NULL;

    unsigned short req_len = 0;

    unsigned char type = 0;

    short result = 0;

    char* dataPtr = NULL;
    char numBuf[10];
    int num = 0;

    type = MQTT_UnPacketRecv(cmd);
    switch(type)
    {
    case MQTT_PKT_CMD: //�����·�

        result = MQTT_UnPacketCmd(cmd, &cmdid_topic, &req_payload, &req_len); //���topic����Ϣ��
        if(result == 0)
        {
            //				UsartPrintf(USART_DEBUG,"cmdid: %s, req: %s, req_len: %d\r\n", cmdid_topic, req_payload, req_len);

            if(strstr((const char*)req_payload, "open"))
                key = 1;
            else if(strstr((const char*)req_payload, "close"))
                key = 0;

            if(MQTT_PacketCmdResp(cmdid_topic, req_payload, &mqttPacket) == 0)  //����ظ����
            {
                //					UsartPrintf(USART_DEBUG,"Tips:	Send CmdResp\r\n");

                ESP8266_SendData(mqttPacket._data, mqttPacket._len); //�ظ�����
                MQTT_DeleteBuffer(&mqttPacket);						 //ɾ��
            }
        }

        break;

    //		case MQTT_PKT_PUBACK:														//����Publish��Ϣ��ƽ̨�ظ���Ack
    //
    //			if(MQTT_UnPacketPublishAck(cmd) == 0)
    //				UsartPrintf(USART_DEBUG,"Tips:	MQTT Publish Send OK\r\n");
    //			else if(MQTT_UnPacketPublishAck(cmd) != 0)
    //				UsartPrintf(USART_DEBUG,"1\r\n");
    //
    //		break;

    default:
        result = -1;
        break;
    }

    ESP8266_Clear(); //��ջ���

    if(result == -1)
        return;

    dataPtr = strchr(req_payload, '}'); //����'}'

    if(dataPtr != NULL && result != -1)  //����ҵ���
    {
        dataPtr++;

        while(*dataPtr >= '0' && *dataPtr <= '9')  //�ж��Ƿ����·��������������
        {
            numBuf[num++] = *dataPtr++;
        }

        num = atoi((const char*)numBuf);  //תΪ��ֵ��ʽ
    }

    if(type == MQTT_PKT_CMD || type == MQTT_PKT_PUBLISH)
    {
        MQTT_FreeBuffer(cmdid_topic);
        MQTT_FreeBuffer(req_payload);
    }

    ESP8266_Clear();
}
