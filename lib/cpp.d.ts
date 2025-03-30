// TypeScript bindings for emscripten-generated code.  Automatically generated at compile time.
declare namespace RuntimeExports {
    let HEAPF32: any;
    let HEAPF64: any;
    let HEAP_DATA_VIEW: any;
    let HEAP8: any;
    let HEAPU8: any;
    let HEAP16: any;
    let HEAPU16: any;
    let HEAP32: any;
    let HEAPU32: any;
    let HEAP64: any;
    let HEAPU64: any;
    let FS_createPath: any;
    function FS_createDataFile(parent: any, name: any, fileData: any, canRead: any, canWrite: any, canOwn: any): void;
    function FS_createPreloadedFile(parent: any, name: any, url: any, canRead: any, canWrite: any, onload: any, onerror: any, dontCreateFile: any, canOwn: any, preFinish: any): void;
    function FS_unlink(path: any): any;
    let FS_createLazyFile: any;
    let FS_createDevice: any;
    let addRunDependency: any;
    let removeRunDependency: any;
}
interface WasmModule {
  _main(_0: number, _1: number): number;
}

export interface ClassHandle {
  isAliasOf(other: ClassHandle): boolean;
  delete(): void;
  deleteLater(): this;
  isDeleted(): boolean;
  clone(): this;
}
export interface Rasterizer extends ClassHandle {
  Draw(): vector<int>;
  Input(_0: boolean, _1: boolean, _2: boolean, _3: boolean, _4: boolean, _5: boolean, _6: number): void;
  Render(_0: number): void;
}

export interface ShadingMethodValue<T extends number> {
  value: T;
}
export type ShadingMethod = ShadingMethodValue<0>|ShadingMethodValue<1>|ShadingMethodValue<2>|ShadingMethodValue<3>;

export interface vector<int> extends ClassHandle {
  push_back(_0: number): void;
  resize(_0: number, _1: number): void;
  size(): number;
  get(_0: number): number | undefined;
  set(_0: number, _1: number): boolean;
}

interface EmbindModule {
  Rasterizer: {
    new(_0: number, _1: number, _2: ShadingMethod): Rasterizer;
  };
  ShadingMethod: {WIREFRAMED: ShadingMethodValue<0>, FLAT_SHADING: ShadingMethodValue<1>, GOUREAU_SHADING: ShadingMethodValue<2>, PONG_SHADING: ShadingMethodValue<3>};
  vector<int>: {
    new(): vector<int>;
  };
}

export type MainModule = WasmModule & typeof RuntimeExports & EmbindModule;
export default function MainModuleFactory (options?: unknown): Promise<MainModule>;
