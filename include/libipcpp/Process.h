#ifndef LIBIPC_PROCESS_H
#define LIBIPC_PROCESS_H

#ifdef _MSC_VER
#pragma once
#endif

#include "Definitions.h"

namespace ipc {
    //! Diese Klasse speichert wichtige Prozessdaten
    class LIBIPC_API ProcessInfo
    {
    public:
        //! Erzeugt eine neue Klasse
        ProcessInfo() = default;
        //! Standard Kopierkonstruktor
        ProcessInfo(const ProcessInfo&) = default;
        //! Standard Destruktor
        ~ProcessInfo() = default;

#ifdef _MSC_VER
        ProcessInfo(ProcessInfo&&);
#else
        ProcessInfo(ProcessInfo&&) = default;
#endif

        /*!
         * Retouniert die Prozess ID. Kann aber auch -1 im Falle eines
         * invaliden Prozesses retounieren.
         *
         * \returns Prozess ID
         */
        int32_t GetId() const NOEXCEPT;

        /*!
         * Retouniert den Namen des Prozesses. Im Falle eines invaliden
         * Prozesses wird eine leere Zeichenkette retouniert.
         *
         * \returns Prozessname
         */
        std::string GetName() const NOEXCEPT;

        /*!
         * Retouniert den nativen Prozess-Handle. Dient dazu um selber auf
         * Systemfunktionen zurückgreifen zu können, falls die angebotene API
         * nicht den geforderten Ansprüchen genügt.
         *
         * \return Nativer Prozess-Handle.
         */
        ProcessHandle GetHandle() const NOEXCEPT;

    private:
        int32_t mId = 0;
        std::string mName = "";
        ProcessHandle mHandle = PROCESS_NULL_HANDLE;

        friend class Process;
    };

    class LIBIPC_API Process : public ReferenceType
    {
    public:

        /*!
         * Erzeugt einen neuen Prozess. Der Prozess wird jedoch noch nicht
         * ausgeführt sondern lediglich auf eine Ausführung vorbereitet. Um den
         * Prozess auszuführen, muss die Methode Process::Start ausgeführt
         * werden.
         *
         * \b Exceptions:
         * - IpcException
         */
        Process() throw(IpcException);

        /*!
         * Dieser Konstruktor dient dazu einen Prozess bspw zwischen
         * Threads verschieben zu können. Es ist wichtig das es immer nur
         * ein valides Prozessobjekt gibt. Dies gilt jedoch nicht für den
         * Fall von Systemprozessen bzw Prozesse die keine Kindprozesse vom
         * Programm darstellen, da jene Prozesse von einen anderen Besitzer
         * erzeugt wurden.
         *
         * \params[in,out] p Der Prozess der verschoben wird. 
         */
        Process(Process&& p);

        /*!
         * Es gilt zu beachten dass der Destruktor eines erzeugten Prozesses
         * nicht exception safe ist. Solange der Prozess läuft und nicht vom
         * ausführenden Prozess terminiert wurde, kann der Destruktor eine
         * Exception vom Typ IpcException produzieren.
         *
         * Ein workaround stellen die best practice Beispiele dar.
         */
        virtual ~Process() throw(IpcException);

        /*!
         * Überprüft ob der Prozess in einen validen zustand ist. Falls der
         * Zustand invalide ist, dann kann der Prozess nicht weiter verwendet
         * werden.
         *
         * \returns TRUE wenn der Prozess valide ist, FALSE wenn invalide.
         */
        bool IsValid() const NOEXCEPT;

        /*!
         * Diese Methode liest den Returnwert aus. Falls der Prozess noch
         * noch keinen Exitcode generiert hat, dann wird einer der folgenden
         * Zustände retouniert:
         *
         * \b Zustände:
         * - PROCESS_NOT_RUNNING
         * - PROCESS_STILL_RUNNING
         * - PROCESS_NOT_VALID
         *
         * \returns Den Exitcode vom Prozess.
         */
        int32_t ExitCode() const NOEXCEPT;
        //! Der Prozess läuft nicht.
        static const int32_t PROCESS_NOT_RUNNING = 0x80000000;
        //! Der Prozess läuft noch.
        static const int32_t PROCESS_STILL_RUNNING = 0x80000001;
        //! Der Prozess befindet sich in keinen validen Zustand.
        static const int32_t PROCESS_NOT_VALID = 0x80000002;

        /*!
         * Terminiert den Prozess unabhängig vom seiner Ausführung. Falls der
         * Prozess jedoch nicht terminiert werden kann bzw nicht die nötigen
         * Rechte für diesen Befehl exisiteren, dann wird eine Exception
         * geworfen. Der Zustand des Prozesses ist danach auf Invalid gesetzt.
         *
         * \returns Referenz zum Prozess.
         */
        Process& Kill() throw(IpcException);
        
        /*!
         * Wartet solange bis der Prozess seine Ausführung beendet hat. Falls
         * der Prozess nicht läuft, oder in einen invaliden Zustand ist, dann
         * retouniert die Methode sofort. In allen anderen Fällen blockiert die
         * Methode solange bis der Prozess terminiert ist.
         *
         * \returns Referenz zum Prozess.
         */
        Process& Wait() NOEXCEPT;

        /*!
         * Wartet für eine bestimmte Zeitspanne bis der Prozess beendet wurde.
         * Es gelten die selben Kriterien wie für Process::Wait.
         *
         * \params[in]  timeoutDuration Zeitdauer die gewartet werden soll.
         * \returns TRUE wenn der Prozess terminiert ist, ansonsten FALSE.
         */
        template <typename Rep, typename Period>
        bool WaitFor(const std::chrono::duration<Rep, Period>& timeoutDuration) const NOEXCEPT
        {
            // TODO: implementieren
        }

        /*!
         * Wartet bis zu einen bestimmten Zeitpunkt bis der Prozess terminiert
         * ist. Es gelten die selben Kriterien wie für Process::Wait.
         *
         * \params[in]  timeoutTime Zeitpunkt bis zu dem gewartet werden soll.
         * \returns TRUE wenn der Prozess terminiert ist, ansonsten FALSE.
         */
        template <typename Clock, typename Duration>
        bool WaitUntil(const std::chrono::time_point<Clock, Duration>& timeoutTime) const NOEXCEPT
        {
            // TODO: implementieren
        }

        /*!
         * Erzeugt einen neuen Prozess und führt die mitgegebene Funktion als
         * dessen Main aus. Falls jedoch Fehler beim erstellen oder ausführen
         * stattfinden, dann wird eine IpcException geworfen.
         *
         * \b Exception:
         * - IpcException
         *
         * \params[in]  main    Das Funktionsobjekt das ausgeführt wird.
         * \params[in]  args... Die Argumente die der Funktion übergeben 
         *                      werden.
         * \returns Zeiger auf neu erstellten Prozess.
         */
        template <typename Function, typename... Args>
        static std::shared_ptr<Process> Create(Function&& main, Args&&... args) throw(IpcException)
        {
            // TODO: implementieren
        }

        /*!
         * Retouniert den angegebenen Prozess mit anhand des übergebenen
         * Namen. Falls kein Prozess mit dem spezifizierten Namen existiert,
         * dann wird ein nullptr Objekt retouniert. Falls jedoch mehrere
         * Prozesse mit dem angegebenen Namen existieren, dann wird der erste
         * Fund retouniert.
         *
         * \returns Prozess mit angegebenen Namen.
         */
        static std::shared_ptr<Process> GetProcessByName(const std::string&) NOEXCEPT;

        /*!
         * Retouniert eine Liste aller aktuell laufenden Prozesse. Es sei
         * angemerkt dass Prozesse die nicht vom Programm erzeugt wurden, von
         * diesen auch nicht terminiert werden könne.
         *
         * \returns List aller im Moment laufenden Prozesse.
         */
        static std::vector<ProcessInfo> GetProcesses() NOEXCEPT;

    protected:

    private:

        Process(const Process&) = delete;
    };
}

#endif
