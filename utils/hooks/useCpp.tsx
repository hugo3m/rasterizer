"use client";

import { useState, useEffect, createContext, useContext, ReactNode } from 'react';
import { MainModule } from "@/lib/cpp.js";

const CppContext = createContext<MainModule | undefined>(undefined);

interface CppProviderProps {
  children: ReactNode;
}

const CppProvider = ({ children }: CppProviderProps) => {
  const [module, setModule] = useState<MainModule | undefined>(undefined);

  useEffect(() => {
    const init = async () => {
      const mainModule: MainModule = await (await import('../../lib/cpp.js')).default();
      setModule(mainModule);
    };
    init();
  }, []);

  return (
    <CppContext.Provider value={module}>
      {children}
    </CppContext.Provider>
  );
};

const useCpp = (): MainModule | undefined => {
  const context = useContext(CppContext);
  return context;
};

export {
  CppProvider,
  useCpp
};