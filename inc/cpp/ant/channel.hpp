#ifndef __INC_WHAD_ANT_CHANNEL_HPP
#define __INC_WHAD_ANT_CHANNEL_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include "ant/base.hpp"

namespace whad::ant {

    class SetDeviceNumber : public AntMsg
    {
        public:

            /* Constructors. */
            SetDeviceNumber(AntMsg &message);
            SetDeviceNumber(uint32_t channel_number, uint32_t device_number);

            uint32_t getChannelNumber();
            uint32_t getDeviceNumber();

        private:
            uint32_t m_channel_number;
            uint32_t m_device_number;

            void pack();
            void unpack();
    };


    class SetDeviceType : public AntMsg
    {
        public:

            /* Constructors. */
            SetDeviceType(AntMsg &message);
            SetDeviceType(uint32_t channel_number, uint32_t device_type);

            uint32_t getChannelNumber();
            uint32_t getDeviceType();

        private:
            uint32_t m_channel_number;
            uint32_t m_device_type;

            void pack();
            void unpack();
    };


    class SetTransmissionType : public AntMsg
    {
        public:

            /* Constructors. */
            SetTransmissionType(AntMsg &message);
            SetTransmissionType(uint32_t channel_number, uint32_t transmission_type);

            uint32_t getChannelNumber();
            uint32_t getTransmissionType();

        private:
            uint32_t m_channel_number;
            uint32_t m_transmission_type;

            void pack();
            void unpack();
    };



    class SetChannelPeriod : public AntMsg
    {
        public:

            /* Constructors. */
            SetChannelPeriod(AntMsg &message);
            SetChannelPeriod(uint32_t channel_number, uint32_t channel_period);

            uint32_t getChannelNumber();
            uint32_t getChannelPeriod();

        private:
            uint32_t m_channel_number;
            uint32_t m_channel_period;

            void pack();
            void unpack();
    };

    class AssignChannel : public AntMsg
    {
        public:

            /* Constructors. */
            AssignChannel(AntMsg &message);
            AssignChannel(
                            uint32_t channel_number, uint32_t network_number, 
                            ChannelType channel_type, bool background_scanning, 
                            bool frequency_agility, bool fast_channel_initiation, 
                            bool asynchronous_transmission
                        );

            uint32_t getChannelNumber();
            uint32_t getNetworkNumber();
            ChannelType getChannelType();
            bool getBackgroundScanning();
            bool getFrequencyAgility();
            bool getFastChannelInitiation();
            bool getAsynchronousTransmission();

        private:

            uint32_t m_channel_number;
            uint32_t m_network_number; 
            ChannelType m_channel_type; 
            bool m_background_scanning; 
            bool m_frequency_agility;
            bool m_fast_channel_initiation;
            bool m_asynchronous_transmission;

            void pack();
            void unpack();
    };


    class UnassignChannel : public AntMsg
    {
        public:

            /* Constructors. */
            UnassignChannel(AntMsg &message);
            UnassignChannel(uint32_t channel_number);

            uint32_t getChannelNumber();

        private:

            uint32_t m_channel_number;

            void pack();
            void unpack();
    };


    class OpenChannel : public AntMsg
    {
        public:

            /* Constructors. */
            OpenChannel(AntMsg &message);
            OpenChannel(uint32_t channel_number);

            uint32_t getChannelNumber();

        private:

            uint32_t m_channel_number;
            
            void pack();
            void unpack();
    };


    class CloseChannel : public AntMsg
    {
        public:

            /* Constructors. */
            CloseChannel(AntMsg &message);
            CloseChannel(uint32_t channel_number);

            uint32_t getChannelNumber();

        private:

            uint32_t m_channel_number;
            
            void pack();
            void unpack();
    };


    class SetRFChannel : public AntMsg
    {
        public:

            /* Constructors. */
            SetRFChannel(AntMsg &message);
            SetRFChannel(uint32_t channel_number, uint32_t rf_channel);

            uint32_t getChannelNumber();
            uint32_t getRFChannel();

        private:

            uint32_t m_channel_number;
            uint32_t m_rf_channel;
            
            void pack();
            void unpack();
    };

    class ListChannels : public AntMsg
    {
        public:
            ListChannels(AntMsg &message);
            ListChannels();

        private:
            void pack();
    };

    class AvailableChannels : public AntMsg
    {
        public:
            AvailableChannels(AntMsg &message);
            AvailableChannels(uint32_t number_of_channels);

            uint32_t getNumberOfChannels();

        private:
            void pack();
            void unpack();

            uint32_t m_number_of_channels;
    };


    class ChannelEvent : public AntMsg
    {
        public:
            ChannelEvent(AntMsg &message);
            ChannelEvent(uint32_t channel_number, ChannelEventCode event);

            uint32_t getChannelNumber();
            ChannelEventCode getEvent();


        private:
            void pack();
            void unpack();

            uint32_t m_channel_number;
            ChannelEventCode m_event;
    };
}

#endif /* __INC_WHAD_ANT_CHANNEL_HPP */