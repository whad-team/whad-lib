#include "ringbuf.h"

/**
 * @brief   Initialize a ring buffer.
 * @param   p_ringbuf   Pointer to a `whad_ringbuf_t` structure.
 **/

void whad_ringbuf_init(whad_ringbuf_t *p_ringbuf)
{
    /* Set ringbuf head & tail. */
    p_ringbuf->head = 0;
    p_ringbuf->tail = 0;
}


/**
 * @brief   Get ring buffer size
 * @param   p_ringbuf   Pointer to a `whad_ringbuf_t` structure.
 * @return  Number of bytes stored in the ring buffer.
 */

int whad_ringbuf_get_size(whad_ringbuf_t *p_ringbuf)
{
    return (WHAD_RINGBUF_MAX_SIZE + p_ringbuf->head - p_ringbuf->tail) % WHAD_RINGBUF_MAX_SIZE;
}

/**
 * @brief   Push data into a ring buffer.
 * @param   p_ringbuf   Pointer to a `whad_ringbuf_t` structure.
 * @param   data    Data to save into the ring buffer.
 * @return  WHAD_SUCCESS on success, WHAD_RINGBUF_FULL if buffer is full.
 */

whad_result_t whad_ringbuf_push(whad_ringbuf_t *p_ringbuf, uint8_t data)
{
    int new_head;

    /* Do we have enough space ? */
    if (whad_ringbuf_get_size(p_ringbuf) >= 1)
    {
        /* Update head and save data. */
        new_head = (p_ringbuf->head + 1)%WHAD_RINGBUF_MAX_SIZE;
        p_ringbuf->data[new_head] = data;
        p_ringbuf->head = new_head;

        /* Success. */
        return WHAD_SUCCESS;
    }

    return WHAD_RINGBUF_FULL;
}


/**
 * @brief   Retrieve data from a ring buffer.
 * @param   p_ringbuf   Pointer to a `whad_ringbuf_t` structure.
 * @param   p_data    Pointer to a uint8_t variable to receive the data.
 * @return  WHAD_SUCCESS on success, WHAD_RINGBUF_EMPTY if buffer is empty.
 */

whad_result_t whad_ringbuf_pull(whad_ringbuf_t *p_ringbuf, uint8_t *p_data)
{
    int new_tail;

    /* Do we have some remaining data ? */
    if (whad_ringbuf_get_size(p_ringbuf) > 0)
    {
        *p_data = p_ringbuf->data[p_ringbuf->tail];
        new_tail = (p_ringbuf->tail + 1)%WHAD_RINGBUF_MAX_SIZE;
        p_ringbuf->tail = new_tail;

        /* Success. */
        return WHAD_SUCCESS;
    }
    else
        return WHAD_RINGBUF_EMPTY;
}

whad_result_t whad_ringbuf_copy(whad_ringbuf_t *p_ringbuf, uint8_t *p_data, int size)
{
    int fh=0, sh=0;

    /* We cannot retrieve more data our ring buffer can hold. */
    if (size > whad_ringbuf_get_size(p_ringbuf))
        return WHAD_ERROR;

    /* Determine first and second halves. */
    if ((p_ringbuf->head + size) > WHAD_RINGBUF_MAX_SIZE)
    {
        fh = (WHAD_RINGBUF_MAX_SIZE - p_ringbuf->head);
        sh = (p_ringbuf->head + size)%WHAD_RINGBUF_MAX_SIZE;
    }
    else
    {
        fh = size;
    }

    /* Copy data. */
    if (fh > 0)
    {
        memcpy(p_data, &p_ringbuf->data[p_ringbuf->head], fh);
    }
    if (sh > 0)
    {
        memcpy(&p_data[fh], p_ringbuf->data[0], sh);
    }

    /* Success. */
    return WHAD_SUCCESS;
}


whad_result_t whad_ringbuf_skip(whad_ringbuf_t *p_ringbuf, int size)
{
    /* Are we trying to skip more bytes than the ring buffer holds ?*/
    if (whad_ringbuf_get_size(p_ringbuf) < size)
        return WHAD_ERROR;

    /* Increment tail. */
    p_ringbuf->tail = (p_ringbuf->tail + size) % WHAD_RINGBUF_MAX_SIZE;

    /* Success. */
    return WHAD_SUCCESS;
}