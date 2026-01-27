# DataProducts::Producer

A data product producer that creates a container composed of sinusoidal data records. Each record contains a timestamp
and a sinusoidal value. The component requests a data product container, fills it with generated data, and sends it
out via the data product send port.

Sinusoidal data is generated on the rate group schedule input port using the system time.

