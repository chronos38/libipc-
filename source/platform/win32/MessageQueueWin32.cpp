#include <libipcpp\MessageQueue.h>
#include <libipcpp\Utility.h>
#include <Mq.h>

using string = std::string;
#define BUFLEN 256

namespace ipc {
    HRESULT CreateQueue(LPWSTR wszPathName, PSECURITY_DESCRIPTOR pSecurityDescriptor, LPWSTR wszOutFormatName, DWORD *pdwOutFormatNameLength);
    HRESULT ReadingDestinationQueue(WCHAR* wszQueueName, WCHAR* wszComputerName, UCHAR** message);
    HRESULT SendMessage(WCHAR* wszQueueName, WCHAR* wszComputerName, UCHAR* buffer);

    MessageQueue::MessageQueue(const string& fileName)
    {
        DWORD length = 1024;
        WCHAR name[1024];
        SECURITY_ATTRIBUTES attr;
        memset(&attr, 0, sizeof(attr));
        attr.bInheritHandle = TRUE;


    }

    MessageQueue::~MessageQueue()
    {

    }

    void MessageQueue::SendMessage(const Message& message)
    {

    }

    Message& MessageQueue::ReceiveMessage(Message& message)
    {
        return message;
    }

    Message& MessageQueue::ReceiveMessage(Message& message, PriorityId id)
    {
        return message;
    }

    HRESULT CreateQueue(LPWSTR wszPathName, PSECURITY_DESCRIPTOR pSecurityDescriptor, LPWSTR wszOutFormatName, DWORD *pdwOutFormatNameLength)
    {
        // Define the maximum number of queue properties.
        const int NUMBEROFPROPERTIES = 2;


        // Define a queue property structure and the structures needed to initialize it.
        MQQUEUEPROPS   QueueProps;
        MQPROPVARIANT  aQueuePropVar[NUMBEROFPROPERTIES];
        QUEUEPROPID    aQueuePropId[NUMBEROFPROPERTIES];
        HRESULT        aQueueStatus[NUMBEROFPROPERTIES];
        HRESULT        hr = MQ_OK;


        // Validate the input parameters.
        if (wszPathName == NULL || wszOutFormatName == NULL || pdwOutFormatNameLength == NULL) {
            return MQ_ERROR_INVALID_PARAMETER;
        }


        // Set queue properties.
        DWORD cPropId = 0;
        aQueuePropId[cPropId] = PROPID_Q_PATHNAME;
        aQueuePropVar[cPropId].vt = VT_LPWSTR;
        aQueuePropVar[cPropId].pwszVal = wszPathName;
        cPropId++;

        WCHAR wszLabel[MQ_MAX_Q_LABEL_LEN] = L"Test Queue";
        aQueuePropId[cPropId] = PROPID_Q_LABEL;
        aQueuePropVar[cPropId].vt = VT_LPWSTR;
        aQueuePropVar[cPropId].pwszVal = wszLabel;
        cPropId++;


        // Initialize the MQQUEUEPROPS structure.
        QueueProps.cProp = cPropId;               // Number of properties
        QueueProps.aPropID = aQueuePropId;        // IDs of the queue properties
        QueueProps.aPropVar = aQueuePropVar;      // Values of the queue properties
        QueueProps.aStatus = aQueueStatus;        // Pointer to the return status


        // Call MQCreateQueue to create the queue.
        WCHAR wszFormatNameBuffer[BUFLEN];
        DWORD dwFormatNameBufferLength = BUFLEN;
        hr = MQCreateQueue(pSecurityDescriptor,         // Security descriptor
                           &QueueProps,                 // Address of queue property structure
                           wszFormatNameBuffer,         // Pointer to format name buffer
                           &dwFormatNameBufferLength);  // Pointer to receive the queue's format name length in Unicode characters not bytes.


        // Return the format name if the queue is created successfully.
        if (hr == MQ_OK || hr == MQ_INFORMATION_PROPERTY) {
            if (*pdwOutFormatNameLength >= dwFormatNameBufferLength) {
                wcsncpy_s(wszOutFormatName, *pdwOutFormatNameLength - 1, wszFormatNameBuffer, _TRUNCATE);
                // ************************************
                // You must copy wszFormatNameBuffer into the 
                // wszOutFormatName buffer.
                // ************************************
                wszOutFormatName[*pdwOutFormatNameLength - 1] = L'\0';
                *pdwOutFormatNameLength = dwFormatNameBufferLength;
            }/* else {
                wprintf(L"The queue was created, but its format name cannot be returned.\n");
            }*/
        }
        return hr;
    }

    HRESULT ReadingDestinationQueue(WCHAR* wszQueueName, WCHAR* wszComputerName, UCHAR** message)
    {

        // Define the required constants and variables.
        const int NUMBEROFPROPERTIES = 5;
        DWORD cPropId = 0;
        HRESULT hr = MQ_OK;                                 // Return code
        HANDLE hQueue = NULL;                               // Queue handle
        ULONG ulBufferSize = 2;


        // Define an MQMSGPROPS structure.
        MQMSGPROPS msgprops;
        MSGPROPID aMsgPropId[NUMBEROFPROPERTIES];
        MQPROPVARIANT aMsgPropVar[NUMBEROFPROPERTIES];
        HRESULT aMsgStatus[NUMBEROFPROPERTIES];


        // Specify the message properties to be retrieved.
        aMsgPropId[cPropId] = PROPID_M_LABEL_LEN;           // Property ID
        aMsgPropVar[cPropId].vt = VT_UI4;                   // Type indicator
        aMsgPropVar[cPropId].ulVal = MQ_MAX_MSG_LABEL_LEN;  // Length of label
        cPropId++;

        WCHAR wszLabelBuffer[MQ_MAX_MSG_LABEL_LEN];         // Label buffer
        aMsgPropId[cPropId] = PROPID_M_LABEL;               // Property ID
        aMsgPropVar[cPropId].vt = VT_LPWSTR;                // Type indicator
        aMsgPropVar[cPropId].pwszVal = wszLabelBuffer;      // Label buffer
        cPropId++;

        UCHAR * pucBodyBuffer = NULL;
        pucBodyBuffer = (UCHAR*)malloc(ulBufferSize);
        if (pucBodyBuffer == NULL) {
            return MQ_ERROR_INSUFFICIENT_RESOURCES;
        }
        memset(pucBodyBuffer, 0, ulBufferSize);
        aMsgPropId[cPropId] = PROPID_M_BODY_SIZE;           // Property ID
        aMsgPropVar[cPropId].vt = VT_NULL;                  // Type indicator
        cPropId++;

        aMsgPropId[cPropId] = PROPID_M_BODY;                // Property ID
        aMsgPropVar[cPropId].vt = VT_VECTOR | VT_UI1;       // Type indicator
        aMsgPropVar[cPropId].caub.pElems = (UCHAR*)pucBodyBuffer;  // Body buffer
        aMsgPropVar[cPropId].caub.cElems = ulBufferSize;    // Buffer size
        cPropId++;

        aMsgPropId[cPropId] = PROPID_M_BODY_TYPE;           // Property ID
        aMsgPropVar[cPropId].vt = VT_NULL;                  // Type indicator
        cPropId++;


        // Initialize the MQMSGPROPS structure.
        msgprops.cProp = cPropId;                           // Number of message properties
        msgprops.aPropID = aMsgPropId;                      // IDs of the message properties
        msgprops.aPropVar = aMsgPropVar;                    // Values of the message properties
        msgprops.aStatus = aMsgStatus;                      // Error reports


        // Validate the input strings.
        if (wszQueueName == NULL || wszComputerName == NULL) {
            return MQ_ERROR_INVALID_PARAMETER;
        }


        // Create a direct format name.
        WCHAR * wszFormatName = NULL;
        DWORD dwFormatNameLength = 0;
        dwFormatNameLength = wcslen(wszQueueName) + wcslen(wszComputerName) + 12;
        wszFormatName = new WCHAR[dwFormatNameLength];
        if (wszFormatName == NULL) {
            return MQ_ERROR_INSUFFICIENT_RESOURCES;
        }
        memset(wszFormatName, 0, dwFormatNameLength);
        // ************************************
        // You must concatenate "DIRECT=OS:", wszComputerName, "\", 
        // and wszQueueName into the wszFormatName buffer.
        // wszFormatName = "DIRECT=OS:" + wszComputerName + "\" +   
        // wszQueueName
        // If the format name is too long for the buffer, return FALSE.
        // ************************************

        // Open the queue with receive access.
        hr = MQOpenQueue(
            wszFormatName,                      // Format name of the queue
            MQ_RECEIVE_ACCESS,                  // Access mode
            MQ_DENY_NONE,                       // Share mode
            &hQueue                             // OUT: Queue handle
            );
        // Free the memory that was allocated for the format name string.
        if (wszFormatName) {
            delete[] wszFormatName;
        }


        // Handle any error returned by MQOpenQueue.
        if (FAILED(hr)) {
            return hr;
        }

        for (;;) {
            aMsgPropVar[0].ulVal = MQ_MAX_MSG_LABEL_LEN;
            hr = MQReceiveMessage(
                hQueue,                     // Queue handle
                1000,                       // Max time to (msec) to receive the message
                MQ_ACTION_RECEIVE,          // Receive action
                &msgprops,                  // Message property structure
                NULL,                       // No OVERLAPPED structure
                NULL,                       // No callback function
                NULL,                       // No cursor handle
                MQ_NO_TRANSACTION           // Not in a transaction
                );

            if (hr == MQ_ERROR_BUFFER_OVERFLOW) {
                ulBufferSize = aMsgPropVar[2].ulVal*sizeof(UCHAR);
                pucBodyBuffer = (UCHAR*)realloc(pucBodyBuffer, ulBufferSize);
                if (pucBodyBuffer == NULL) {
                    return MQ_ERROR_INSUFFICIENT_RESOURCES;
                }
                memset(pucBodyBuffer, 0, ulBufferSize);
                aMsgPropVar[3].caub.pElems = (UCHAR*)pucBodyBuffer;
                aMsgPropVar[3].caub.cElems = ulBufferSize;
                continue;
            }

            if (FAILED(hr)) {
                //wprintf(L"No messages. Closing queue\n");
                break;
            }

            // If the message contains a label, print it.
            /*if (msgprops.aPropVar[0].ulVal == 0) {
                wprintf(L"Removed message from queue.\n");
            } else {
                wprintf(L"Removed message '%s' from queue.\n", wszLabelBuffer);
            }


            // If the message body is a string, display it.
            if (msgprops.aPropVar[4].ulVal == VT_BSTR) {
                wprintf(L"Body: %s", (WCHAR*)pucBodyBuffer);
                wprintf(L"\n");
            }*/

            // Save message
            *message = pucBodyBuffer;
            break;
        }


        // Close the queue and free the memory allocated for the body buffer.
        hr = MQCloseQueue(hQueue);
        //free(pucBodyBuffer);
        // TODO: Do not forget to free the memory

        return hr;
    }

    HRESULT SendMessage(WCHAR* wszQueueName, WCHAR* wszComputerName, UCHAR* buffer)
    {

        // Validate the input strings.
        if (wszQueueName == NULL || wszComputerName == NULL) {
            return MQ_ERROR_INVALID_PARAMETER;
        }


        // Define the required constants and variables.
        const int NUMBEROFPROPERTIES = 5;                   // Number of properties
        DWORD cPropId = 0;                                  // Property counter
        HRESULT hr = MQ_OK;                                 // Return code
        HANDLE hQueue = NULL;                               // Queue handle

        // Define an MQMSGPROPS structure.
        MQMSGPROPS msgProps;
        MSGPROPID aMsgPropId[NUMBEROFPROPERTIES];
        MQPROPVARIANT aMsgPropVar[NUMBEROFPROPERTIES];
        HRESULT aMsgStatus[NUMBEROFPROPERTIES];


        // Specify the message properties to be sent.
        aMsgPropId[cPropId] = PROPID_M_LABEL;               // Property ID
        aMsgPropVar[cPropId].vt = VT_LPWSTR;                // Type indicator
        aMsgPropVar[cPropId].pbVal = buffer;                // The message buffer
        cPropId++;


        // Initialize the MQMSGPROPS structure.
        msgProps.cProp = cPropId;
        msgProps.aPropID = aMsgPropId;
        msgProps.aPropVar = aMsgPropVar;
        msgProps.aStatus = aMsgStatus;


        // Create a direct format name for the queue.
        WCHAR * wszFormatName = NULL;
        DWORD dwBufferLength = 0;
        const WCHAR * wszFormatStr = L"DIRECT=OS:%s\\%s";
        dwBufferLength = wcslen(wszQueueName) + wcslen(wszComputerName) +
            wcslen(wszFormatStr) - 4;

        wszFormatName = new WCHAR[dwBufferLength];
        if (wszFormatName == NULL) {
            return MQ_ERROR_INSUFFICIENT_RESOURCES;
        }
        memset(wszFormatName, 0, dwBufferLength*sizeof(WCHAR));

        if (_snwprintf_s(
            wszFormatName,
            dwBufferLength,
            dwBufferLength - 1,
            L"DIRECT=OS:%s\\%s",
            wszComputerName,
            wszQueueName
            ) < 0) {
            //wprintf(L"The format name is too long for the buffer specified.\n");
            return FALSE;
        } else {
            wszFormatName[dwBufferLength - 1] = L'\0';
        }


        // Call MQOpenQueue to open the queue with send access.
        hr = MQOpenQueue(
            wszFormatName,                     // Format name of the queue
            MQ_SEND_ACCESS,                    // Access mode
            MQ_DENY_NONE,                      // Share mode
            &hQueue                            // OUT: Queue handle
            );
        // Free the memory that was allocated for the format name string.
        delete[] wszFormatName;


        // Handle any error returned by MQOpenQueue.
        if (FAILED(hr)) {
            return hr;
        }


        // Call MQSendMessage to send the message to the queue.
        hr = MQSendMessage(
            hQueue,                          // Queue handle
            &msgProps,                       // Message property structure
            MQ_NO_TRANSACTION               // Not in a transaction
            );
        if (FAILED(hr)) {
            MQCloseQueue(hQueue);
            return hr;
        }


        // Call MQCloseQueue to close the queue.
        hr = MQCloseQueue(hQueue);

        return hr;
    }
}
