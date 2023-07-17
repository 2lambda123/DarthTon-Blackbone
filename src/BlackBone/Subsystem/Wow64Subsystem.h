#pragma once

#include "NativeSubsystem.h"

namespace blackbone
{

class NativeWow64 : public Native
{
public:
    BLACKBONE_API NativeWow64( HANDLE hProcess ) noexcept;
    BLACKBONE_API ~NativeWow64() = default;

    /// <summary>
    /// Allocate virtual memory
    /// </summary>
    /// <param name="lpAddress">Allocation address</param>
    /// <param name="dwSize">Region size</param>
    /// <param name="flAllocationType">Allocation type</param>
    /// <param name="flProtect">Memory protection</param>
    /// <returns>Status code</returns>
    virtual NTSTATUS VirtualAllocExT( ptr_t& lpAddress, size_t dwSize, DWORD flAllocationType, DWORD flProtect ) noexcept;

    /// <summary>
    /// Free virtual memory
    /// </summary>
    /// <param name="lpAddress">Memory address</param>
    /// <param name="dwSize">Region size</param>
    /// <param name="dwFreeType">Memory release type.</param>
    /// <returns>Status code</returns>
    virtual NTSTATUS VirtualFreeExT( ptr_t lpAddress, size_t dwSize, DWORD dwFreeType ) noexcept;

    /// <summary>
    /// Change memory protection
    /// </summary>
    /// <param name="lpAddress">Memory address.</param>
    /// <param name="dwSize">Region size</param>
    /// <param name="flProtect">New protection.</param>
    /// <param name="flOld">Old protection</param>
    /// <returns>Status code</returns>
    virtual NTSTATUS VirtualProtectExT( ptr_t lpAddress, DWORD64 dwSize, DWORD flProtect, DWORD* flOld ) noexcept;

    /// <summary>
    /// Read virtual memory
    /// </summary>
    /// <param name="lpBaseAddress">Memory address</param>
    /// <param name="lpBuffer">Output buffer</param>
    /// <param name="nSize">Number of bytes to read</param>
    /// <param name="lpBytes">Number of bytes read</param>
    /// <returns>Status code</returns>
    virtual NTSTATUS ReadProcessMemoryT( ptr_t lpBaseAddress, LPVOID lpBuffer, size_t nSize, DWORD64 *lpBytes = nullptr ) noexcept;

    /// <summary>
    /// Write virtual memory
    /// </summary>
    /// <param name="lpBaseAddress">Memory address</param>
    /// <param name="lpBuffer">Buffer to write</param>
    /// <param name="nSize">Number of bytes to read</param>
    /// <param name="lpBytes">Number of bytes read</param>
    /// <returns>Status code</returns>
    virtual NTSTATUS WriteProcessMemoryT( ptr_t lpBaseAddress, LPCVOID lpBuffer, size_t nSize, DWORD64 *lpBytes = nullptr ) noexcept;

    /// <summary>
    /// Query virtual memory
    /// </summary>
    /// <param name="lpAddress">Address to query</param>
    /// <param name="lpBuffer">Retrieved memory info</param>
    /// <returns>Status code</returns>
    virtual NTSTATUS VirtualQueryExT( ptr_t lpAddress, PMEMORY_BASIC_INFORMATION64 lpBuffer ) noexcept;

    /// <summary>
    /// Query virtual memory
    /// </summary>
    /// <param name="lpAddress">Address to query</param>
    /// <param name="lpBuffer">Retrieved memory info</param>
    /// <returns>Status code</returns>
    virtual NTSTATUS VirtualQueryExT( ptr_t lpAddress, MEMORY_INFORMATION_CLASS infoClass, LPVOID lpBuffer, size_t bufSize ) noexcept;

    /// <summary>
    /// Call NtQueryInformationProcess for underlying process
    /// </summary>
    /// <param name="infoClass">Information class</param>
    /// <param name="lpBuffer">Output buffer</param>
    /// <param name="bufSize">Buffer size</param>
    /// <returns>Status code</returns>
    virtual NTSTATUS QueryProcessInfoT( PROCESSINFOCLASS infoClass, LPVOID lpBuffer, uint32_t bufSize ) noexcept;

    /// <summary>
    /// Call NtSetInformationProcess for underlying process
    /// </summary>
    /// <param name="infoClass">Information class</param>
    /// <param name="lpBuffer">Input buffer</param>
    /// <param name="bufSize">Buffer size</param>
    /// <returns>Status code</returns>
    virtual NTSTATUS SetProcessInfoT( PROCESSINFOCLASS infoClass, LPVOID lpBuffer, uint32_t bufSize ) noexcept;

    /// <summary>
    /// Creates new thread in the remote process
    /// </summary>
    /// <param name="hThread">Created thread handle</param>
    /// <param name="entry">Thread entry point</param>
    /// <param name="arg">Thread argument</param>
    /// <param name="flags">Creation flags</param>
    /// <returns>Status code</returns>
    virtual NTSTATUS CreateRemoteThreadT( HANDLE& hThread, ptr_t entry, ptr_t arg, CreateThreadFlags flags, DWORD access = THREAD_ALL_ACCESS ) noexcept;

    /// <summary>
    /// Get native thread context
    /// </summary>
    /// <param name="hThread">Thread handle.</param>
    /// <param name="ctx">Thread context</param>
    /// <returns>Status code</returns>
    virtual NTSTATUS GetThreadContextT( HANDLE hThread, _CONTEXT64& ctx ) noexcept;

    /// <summary>
    /// Get WOW64 thread context
    /// </summary>
    /// <param name="hThread">Thread handle.</param>
    /// <param name="ctx">Thread context</param>
    /// <returns>Status code</returns>
    virtual NTSTATUS GetThreadContextT( HANDLE hThread, _CONTEXT32& ctx ) noexcept;

    /// <summary>
    /// Set native thread context
    /// </summary>
    /// <param name="hThread">Thread handle.</param>
    /// <param name="ctx">Thread context</param>
    /// <returns>Status code</returns>
    virtual NTSTATUS SetThreadContextT( HANDLE hThread, _CONTEXT64& ctx ) noexcept;

    /// <summary>
    /// Set WOW64 thread context
    /// </summary>
    /// <param name="hThread">Thread handle.</param>
    /// <param name="ctx">Thread context</param>
    /// <returns>Status code</returns>
    virtual NTSTATUS SetThreadContextT( HANDLE hThread, _CONTEXT32& ctx ) noexcept;

    /// <summary>
    /// NtQueueApcThread
    /// </summary>
    /// <param name="hThread">Thread handle.</param>
    /// <param name="func">APC function</param>
    /// <param name="arg">APC argument</param>
    /// <returns>Status code</returns>
    virtual NTSTATUS QueueApcT( HANDLE hThread, ptr_t func, ptr_t arg ) noexcept;

    /// <summary>
    /// Get WOW64 PEB
    /// </summary>
    /// <param name="ppeb">Retrieved PEB</param>
    /// <returns>PEB pointer</returns>
    virtual ptr_t getPEB( _PEB32* ppeb ) noexcept;

    /// <summary>
    /// Get native PEB
    /// </summary>
    /// <param name="ppeb">Retrieved PEB</param>
    /// <returns>PEB pointer</returns>
    virtual ptr_t getPEB( _PEB64* ppeb ) noexcept;

    /// <summary>
    /// Get WOW64 TEB
    /// </summary>
    /// <param name="ppeb">Retrieved TEB</param>
    /// <returns>TEB pointer</returns>
    virtual ptr_t getTEB( HANDLE hThread, _TEB32* pteb ) noexcept;

    /// <summary>
    /// Get native TEB
    /// </summary>
    /// <param name="ppeb">Retrieved TEB</param>
    /// <returns>TEB pointer</returns>
    virtual ptr_t getTEB( HANDLE hThread, _TEB64* pteb ) noexcept;
};

}