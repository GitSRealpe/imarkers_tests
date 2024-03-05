# OPTIHROV Colab

Set of packages to allow colaboration between CIRS (UdG) and CIRTESU (UJI) research lab for the OPTIHROV project.

Steps


interface  --pub(instruction_msg)---> iauv_commader (commander has context and stuff)
interface --pub(imarker_feedback_msg)---> iauv_commander/feedback (commander knows wich callback to execute)

interface --sub(imarker_update)--> iauv_commander/update
