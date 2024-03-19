#ifndef __INC_WHAD_COMMON_HPP
#define __INC_WHAD_COMMON_HPP

#include <string.h>
#include <stdint.h>

#ifdef __cplusplus

#define WHAD_COMMON_DEF_PACKET_SIZE     255

namespace whad {

    /**
     * Generic Whad exceptions
     */

    class WhadException
    {
    };

    class WhadMessageParsingError : public WhadException
    {
    };

    class WhadInvalidSize : public WhadException
    {
        public:

            /* Constructors. */
            WhadInvalidSize();
            WhadInvalidSize(int size, int expectedSize);

            int getExpectedSize();
            int getSize();

        private:

            int m_size;
            int m_expectedSize;
    };

    /**
     * Generic packet class template.
     * 
     * This packet class enforces a maximum size
     * and allows basic packet operations.
     */

    template<int maxSize=255>
    class Packet
    {   
        public:

            /* Constructors. */
            Packet()
            {
                /* No data in this packet. */
                m_size = 0;
            }

            Packet(uint8_t *pBytes, int size)
            {
                /* Set packet bytes. */
                this->setBytes(pBytes, size);
            }

            /* Getters. */
            int getSize()
            {
                return m_size;
            }

            uint8_t *getBytes()
            {
                return m_bytes;
            }

            static int getMaxSize()
            {
                return maxSize;
            }

            /* Setters. */
            void setBytes(uint8_t *pBytes, int size)
            {
                if (size < maxSize)
                {
                    m_size = size;
                    memcpy(m_bytes, pBytes, size);
                }
                else
                {
                    throw WhadInvalidSize(size, this->getMaxSize());
                }
            }


            void set(Packet<maxSize> &packet)
            {
                if (packet.getSize() < this->getMaxSize())
                {
                    m_size = packet.getSize();
                    memcpy(m_bytes, packet.getBytes(), packet.getSize());
                }
                else
                {
                    throw WhadInvalidSize(packet.getSize(), this->getMaxSize());
                }
            }

        private:
            /* Packet properties. */
            uint8_t m_bytes[maxSize];
            int m_size;
    };

    /**
     * Generic device address template
     * 
     * A device address may support various sizes,
     * thus requiring a minimal and maximal size.
     **/

    template<int minSize=0, int maxSize=8>
    class DeviceAddress
    {
        public:

            DeviceAddress()
            {
                /* Address length is set to 0. */
                m_length = 0;
            }

            DeviceAddress(uint8_t *pAddress, int length)
            {
                /* Set device address. */
                if ((length >= minSize) && (length <= maxSize))
                {
                    set(pAddress, length);
                }
                else
                {
                    /* Invalid size. */
                    throw WhadInvalidSize();
                }                
            }

            /* Getters. */
            uint8_t *getBytes()
            {
                return m_address;
            }

            int getLength()
            {
                return m_length;
            }

            int getMinLength()
            {
                return minSize;
            }

            int getMaxLength()
            {
                return maxSize;
            }

            void set(uint8_t *pBytes, int length)
            {
                if ((length >= minSize) && (length <= maxSize))
                {
                    /* Copy address bytes. */
                    m_length = length;
                    memcpy(m_address, pBytes, length);
                }
            }

            /* Operators */

            /* Comparison operator overloading. */
            bool operator==(const DeviceAddress &other)
            {
                return (
                    (m_length == other.getLength()) &&
                    !memcmp(m_address, other.getBytes(), m_length)
                );
            }

            /* Assignment operator overloading. */
            DeviceAddress& operator=(DeviceAddress& other) noexcept
            {
                if (this == &other)
                    return *this;

                int other_length = other.getLength();
                if ((other_length >= minSize) && (other_length <= maxSize))
                {
                    m_length = other_length;
                    memcpy(m_address, other.getBytes(), m_length);
                }

                return *this;
            }

        private:

            uint8_t m_address[maxSize];
            int m_length;
    };
}


#endif /* __cplusplus */

#endif /* __INC_WHAD_COMMON_HPP */