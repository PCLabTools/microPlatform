# This is an example script

Import("projenv")

# access to project construction environment
print(projenv)

# Dump construction environments (for debug purpose)
print(projenv.Dump())

# append extra flags to only project build environment
projenv.Append(CPPDEFINES=[
  "PROJECT_EXTRA_MACRO_1_NAME",
  ("PROJECT_EXTRA_MACRO_2_NAME", "PROJECT_EXTRA_MACRO_2_VALUE")
])