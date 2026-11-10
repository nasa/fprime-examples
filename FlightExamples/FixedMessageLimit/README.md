# Fixed Message Limit Example

This directory contains an example of the Fixed Message Limit pattern. It consists of the
[Processor](./Processor/docs/sdd.md) component, an active component whose rate group tick is admitted onto its queue at
most `FixedMessageLimit.MAX_PENDING` times before further ticks are skipped.

This component is instantiated in the [ExamplesDeployment](../ExamplesDeployment) as `fixedLimitProcessor`.

| Patterns Demonstrated      |
|----------------------------|
| Fixed Message Limit        |
| Internal Port Overflow Hook |
