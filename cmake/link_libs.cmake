# Link Qt libraries
if(USE_QT)
    target_link_libraries(${PROJECT_NAME} Qt6::Core)
    target_link_libraries(${PROJECT_NAME} Qt6::Widgets)
    # Link Qt Property Browser
    if(USE_QT_PROPERTY_BROWSER)
        target_link_libraries(${PROJECT_NAME} ${QT_PROPERTY_BROWSER_LIB})
    endif()
    
endif()

if(USE_VST)
    target_link_libraries(${PROJECT_NAME} ${VST_LIBS})
endif()
