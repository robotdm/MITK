PROJECT(org_blueberry_ui)

SET(PLUGIN_exported_include_suffixes
  src
  src/application
  src/commands
  src/dialogs
  src/guitk
  src/handlers
  src/intro
  src/presentations
  src/services
  src/testing
  src/tweaklets
  src/util
)

MACRO_CREATE_CTK_PLUGIN(EXPORT_DIRECTIVE BERRY_UI
                        EXPORTED_INCLUDE_SUFFIXES ${PLUGIN_exported_include_suffixes})
