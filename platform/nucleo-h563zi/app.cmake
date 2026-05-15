
set(APP_INCS
    ${BASE}/sces-wraps/wrap/inc 
    ${BASE}/platform/${PLATFORM}/cmw
    CACHE STRING ""
)

set(APP_SRCS
    ${BASE}/sces-wraps/wrap-threadx/src/filex.c
    ${BASE}/sces-wraps/wrap-threadx/src/threadx.c
    CACHE STRING ""
)

set(APP_LIBS
    ${BASE}/${APP_PATH}/target/${ARCH}/${PROFILE}/lib${APP}.a
    CACHE STRING ""
)
