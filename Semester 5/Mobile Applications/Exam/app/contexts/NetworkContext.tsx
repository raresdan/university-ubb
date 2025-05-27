import { createContext, useEffect, useState } from "react";
import NetInfo from "@react-native-community/netinfo";

type NetworkContextType = {
  status: boolean;
};

export const NetworkContext = createContext<NetworkContextType | null>(null);

export default function NetworkContextProvider({ children }: any) {
  const [status, setStatus] = useState<boolean>(false);

  useEffect(() => {
    const unsubscribe = NetInfo.addEventListener((state) => {
      setStatus(state.isConnected != null ? state.isConnected : false);

      console.log(`Status change: ${state.isConnected}`);
    });

    return () => unsubscribe();
  }, []);

  return (
    <NetworkContext.Provider
      value={{
        status: status,
      }}
    >
      {children}
    </NetworkContext.Provider>
  );
}
