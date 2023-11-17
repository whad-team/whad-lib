#ifndef INC_WHAD_PROTOCOL_H
#define INC_WHAD_PROTOCOL_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*********************************
 * PHY domain
 ********************************/

whad_result_t whad_phy_supported_frequencies(Message *p_message, phy_SupportedFrequencyRanges_FrequencyRange *p_ranges,
                                             int nb_ranges);
whad_result_t whad_phy_packet_received(Message *p_message, uint32_t frequency, int32_t rssi, uint32_t ts_sec, uint32_t ts_usec,
                              uint8_t *payload, int length);
whad_result_t whad_phy_packet_scheduled(Message *p_message, uint8_t id, bool full);

#ifdef __cplusplus
}
#endif

#endif /* INC_WHAD_PROTOCOL_H */