# Data storage — IoTWaterTankLevelMonitor

This firmware has no database, schema, migration, or retained local queue. A broker subscriber may persist `sensor-to-water distance`, `level estimate`, validity, alert flag, and timestamp in an external store, but that service is not implemented here. The example publisher uses non-retained QoS 0, so offline readings are lost. An external deployment should define tenant ownership, time-series indexes, and a retention policy before storing data.
