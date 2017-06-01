s========================================================================
    CONSOLE APPLICATION : Everquest Project Overview
========================================================================


========================================================================
    CONSOLE APPLICATION : Working on...
========================================================================

Clean up the observer, subject, notify, forEach
Reference https://www.codeproject.com/Articles/328365/Understanding-and-Implementing-Observer-Pattern

Actually, reference this instead:
https://msdn.microsoft.com/en-us/library/ee850490(v=vs.110).aspx?cs-save-lang=1&cs-lang=csharp#code-snippet-1

Experiment with eliminating the observer and subject classes. Use C++/CLI classes instead

========================================================================
    CONSOLE APPLICATION : Class Diagram
========================================================================

Observer
Subject
Commands : Observer .. can update Bot data
Character : Subject .. can attach Commands