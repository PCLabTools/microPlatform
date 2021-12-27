# This is an example script

Import("env")

# access to global construction environment
print(env)

# Dump construction environments (for debug purpose)
print(env.Dump())

# append extra flags to global build environment
# which later will be used to build:
# - frameworks
# - dependent libraries
env.Append(CPPDEFINES=[
  "MACRO_1_NAME",
  ("MACRO_2_NAME", "MACRO_2_VALUE")
])